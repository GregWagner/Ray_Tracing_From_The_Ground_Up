#ifndef _QTRAYTRACER_H_
#define _QTRAYTRACER_H_

#include "World.hpp"

#include <QElapsedTimer>
#include <QImage>
#include <QMainWindow>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QWidget>

#include <vector>

class RenderCanvas;
class RenderThread;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

    private slots:
    void onRenderStart();
    void onRenderPause();
    void onRenderResume();
    void onOpenFile();
    void onSaveFile();
    void onQuit();

    private:
    RenderCanvas* canvas = nullptr;
};

enum {
    Menu_File_Quit = 100,
    Menu_File_Open,
    Menu_File_Save,
    Menu_Render_Start,
    Menu_Render_Pause,
    Menu_Render_Resume
};

class RenderPixel {
    public:
    RenderPixel(int x, int y, int redValue, int green, int blue);

    int x, y;
    int red, green, blue;
};

class RenderCanvas : public QWidget {
    Q_OBJECT

    public:
    explicit RenderCanvas(QWidget* parent = nullptr);
    ~RenderCanvas() override;

    void setImage(const QImage& image);
    QImage getImage() const;

    void renderStart();
    void renderPause();
    void renderResume();

    private slots:
    void onPixelBatch(const QVector<RenderPixel*>& batch);
    void onRenderFinished();

    protected:
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;

    private:
    QImage image;
    World* world = nullptr;
    RenderThread* thread = nullptr;

    long pixelsRendered = 0;
    long pixelsToRender = 0;
};

class RenderThread : public QThread {
    Q_OBJECT

    public:
    explicit RenderThread(RenderCanvas* canvas, World* world,
                          QObject* parent = nullptr);
    ~RenderThread() override;

    void setPixel(int x, int y, int redValue, int green, int blue);
    void pause();
    void resume();

    signals:
    void pixelBatchReady(QVector<RenderPixel*> batch);
    void renderFinished();

    protected:
    void run() override;

    private:
    void notifyCanvas();

    RenderCanvas* canvas = nullptr;
    World* world = nullptr;

    QVector<RenderPixel*> pixels;
    QElapsedTimer timer;
    qint64 lastUpdateTime = 0;
    QMutex mutex;
    QWaitCondition condition;
    bool paused = false;
};

#endif
