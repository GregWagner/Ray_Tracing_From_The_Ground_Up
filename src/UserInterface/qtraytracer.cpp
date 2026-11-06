#include "qtraytracer.hpp"

#include "World.hpp"

#include <QApplication>
#include <QCloseEvent>
#include <QColor>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QStatusBar>
#include <QThread>
#include <Qt>

#include <cstring>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Ray Tracer");
    resize(500, 550);

    canvas = new RenderCanvas(this);
    setCentralWidget(canvas);

    auto* fileMenu = menuBar()->addMenu("&File");
    auto* openAction = fileMenu->addAction("&Open...");
    auto* saveAction = fileMenu->addAction("&Save As...");
    fileMenu->addSeparator();
    auto* quitAction = fileMenu->addAction("E&xit");

    auto* renderMenu = menuBar()->addMenu("&Render");
    auto* startAction = renderMenu->addAction("&Start");
    auto* pauseAction = renderMenu->addAction("&Pause");
    auto* resumeAction = renderMenu->addAction("&Resume");

    saveAction->setEnabled(false);
    startAction->setEnabled(true);
    pauseAction->setEnabled(false);
    resumeAction->setEnabled(false);

    statusBar()->showMessage("Ready", 0);

    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(quitAction, &QAction::triggered, this, &MainWindow::onQuit);
    connect(startAction, &QAction::triggered, this, &MainWindow::onRenderStart);
    connect(pauseAction, &QAction::triggered, this, &MainWindow::onRenderPause);
    connect(resumeAction, &QAction::triggered, this, &MainWindow::onRenderResume);
}

void MainWindow::onRenderStart() {
    if (canvas != nullptr) {
        canvas->renderStart();
        resize(canvas->getImage().width() + 100,
               canvas->getImage().height() + 150);
    }

    if (auto* sbar = statusBar()) {
        sbar->showMessage("Rendering...", 0);
    }
}

void MainWindow::onRenderPause() {
    if (canvas != nullptr) {
        canvas->renderPause();
    }
    if (auto* sbar = statusBar()) {
        sbar->showMessage("Rendering paused", 0);
    }
}

void MainWindow::onRenderResume() {
    if (canvas != nullptr) {
        canvas->renderResume();
    }
    if (auto* sbar = statusBar()) {
        sbar->showMessage("Rendering...", 0);
    }
}

void MainWindow::onOpenFile() {
    const QString path = QFileDialog::getOpenFileName(
        this, "Choose a file", QString(),
        "Images (*.bmp *.png *.jpg *.jpeg *.tif *.tiff)");

    if (path.isEmpty()) {
        return;
    }

    QImage image(path);
    if (image.isNull()) {
        QMessageBox::information(this, "Error", "Sorry, could not load file.");
        return;
    }

    if (canvas != nullptr) {
        canvas->setImage(image);
    }
}

void MainWindow::onSaveFile() {
    const QString path =
        QFileDialog::getSaveFileName(this, "Save File", "render.bmp",
                                     "BMP files (*.bmp);;PNG files (*.png);;JPEG "
                                     "files (*.jpg);;TIFF files (*.tif)");

    if (path.isEmpty() || !canvas) {
        return;
    }

    canvas->getImage().save(path);
}

void MainWindow::onQuit() {
    close();
}

RenderPixel::RenderPixel(int _x, int _y, int _red, int _green, int _blue)
    : x(_x), y(_y), red(_red), green(_green), blue(_blue) {}

RenderCanvas::RenderCanvas(QWidget* parent) : QWidget(parent) {
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(143, 144, 150));
    setPalette(pal);
}

RenderCanvas::~RenderCanvas() {
    if (thread != nullptr) {
        thread->requestInterruption();
        thread->resume();
        thread->wait();
        delete thread;
        thread = nullptr;
    }

    delete world;
    world = nullptr;
}

void RenderCanvas::setImage(const QImage& inImage) {
    image = inImage;
    update();
}

QImage RenderCanvas::getImage() const {
    return image;
}

void RenderCanvas::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    if (!image.isNull()) {
        painter.drawImage(0, 0, image);
    }
}

QSize RenderCanvas::sizeHint() const {
    if (!image.isNull()) {
        return image.size();
    }
    return QSize(400, 400);
}

void RenderCanvas::renderStart() {
    if (thread != nullptr) {
        thread->requestInterruption();
        thread->resume();
        thread->wait();
        delete thread;
        thread = nullptr;
    }

    delete world;
    world = new World();
    world->build();

    pixelsRendered = 0;
    pixelsToRender =
        static_cast<long>(world->vp.hres) * static_cast<long>(world->vp.vres);

    QImage bitmap(world->vp.hres, world->vp.vres, QImage::Format_RGB32);
    bitmap.fill(QColor(143, 144, 150));
    setImage(bitmap);

    thread = new RenderThread(this, world, this);
    connect(thread, &RenderThread::pixelBatchReady, this,
            &RenderCanvas::onPixelBatch, Qt::QueuedConnection);
    connect(thread, &RenderThread::renderFinished, this,
            &RenderCanvas::onRenderFinished, Qt::QueuedConnection);

    world->paintArea = thread;
    thread->start();
}

void RenderCanvas::renderPause() {
    if (thread != nullptr) {
        thread->pause();
    }
}

void RenderCanvas::renderResume() {
    if (thread != nullptr) {
        thread->resume();
    }
}

void RenderCanvas::onPixelBatch(const QVector<RenderPixel*>& batch) {
    for (RenderPixel* pixel : batch) {
        if (pixel != nullptr && !image.isNull() && pixel->x >= 0 && pixel->y >= 0 &&
            pixel->x < image.width() && pixel->y < image.height()) {
            image.setPixelColor(pixel->x, pixel->y,
                                QColor(pixel->red, pixel->green, pixel->blue));
        }

        pixelsRendered++;
        delete pixel;
    }

    update();
}

void RenderCanvas::onRenderFinished() {
    if (thread != nullptr) {
        thread->wait();
        delete thread;
        thread = nullptr;
    }

    if (world != nullptr) {
        delete world;
        world = nullptr;
    }
}

RenderThread::RenderThread(RenderCanvas* canvasIn, World* worldIn,
                           QObject* parent)
    : QThread(parent), canvas(canvasIn), world(worldIn) {}

RenderThread::~RenderThread() {}

void RenderThread::setPixel(int x, int y, int redValue, int green, int blue) {
    {
        QMutexLocker locker(&mutex);
        while (paused && !isInterruptionRequested()) {
            condition.wait(&mutex);
        }

        if (isInterruptionRequested()) {
            return;
        }
    }

    pixels.append(new RenderPixel(x, y, redValue, green, blue));

    if (timer.elapsed() - lastUpdateTime > 40) {
        notifyCanvas();
    }

    if (isInterruptionRequested()) {
        return;
    }
}

void RenderThread::pause() {
    QMutexLocker locker(&mutex);
    paused = true;
}

void RenderThread::resume() {
    QMutexLocker locker(&mutex);
    paused = false;
    condition.wakeAll();
}

void RenderThread::run() {
    lastUpdateTime = 0;
    timer.start();

    world->camera_ptr->render_scene(*world);

    notifyCanvas();
    emit renderFinished();
}

void RenderThread::notifyCanvas() {
    lastUpdateTime = timer.elapsed();

    auto* batch = new QVector<RenderPixel*>(pixels);
    pixels.clear();

    emit pixelBatchReady(*batch);
    delete batch;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}

void World::display_pixel(const int row, const int column,
                          const RGBColor& raw_color) const {
    RGBColor mapped_color;

    if (vp.show_out_of_gamut) {
        mapped_color = clamp_to_color(raw_color);
    } else {
        mapped_color = max_to_one(raw_color);
    }

    if (vp.gamma != 1.0) {
        mapped_color = mapped_color.powc(vp.inv_gamma);
    }

    int x = column;
    int y = vp.vres - row - 1;

    if (paintArea != nullptr) {
        paintArea->setPixel(x, y, static_cast<int>(mapped_color.r * 255),
                            static_cast<int>(mapped_color.g * 255),
                            static_cast<int>(mapped_color.b * 255));
    }
}
