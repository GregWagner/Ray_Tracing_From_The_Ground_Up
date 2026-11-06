#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include "wxraytracer.hpp"
#include "World.hpp"
#include "main.xpm"
#include "bg.xpm"


/******************************************************************************/
/********************* wxraytracerapp *****************************************/
/******************************************************************************/


BEGIN_EVENT_TABLE(wxraytracerapp, wxApp)
END_EVENT_TABLE()

IMPLEMENT_APP(wxraytracerapp)

bool wxraytracerapp::OnInit() {
	wxInitAllImageHandlers();

	frame = new wxraytracerFrame(wxPoint(200, 200), wxSize(700, 500));
	frame->Centre();
	frame->Show(TRUE);
	SetTopWindow(frame);
	return TRUE;
}

int wxraytracerapp::OnExit() {
	return 0;
}

void wxraytracerapp::SetStatusText(const wxString& text, int number) {
	frame->SetStatusText(text, number);
}

/******************************************************************************/
/********************* wxraytracerFrame ***************************************/
/******************************************************************************/

BEGIN_EVENT_TABLE(wxraytracerFrame, wxFrame)
EVT_MENU(Menu_Render_Start, wxraytracerFrame::OnRenderStart)
EVT_MENU(Menu_Render_Pause, wxraytracerFrame::OnRenderPause)
EVT_MENU(Menu_Render_Resume, wxraytracerFrame::OnRenderResume)
EVT_MENU(Menu_File_Save, wxraytracerFrame::OnSaveFile)
EVT_MENU(Menu_File_Open, wxraytracerFrame::OnOpenFile)
EVT_MENU(Menu_File_Quit, wxraytracerFrame::OnQuit)
EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER,
			wxraytracerFrame::OnRenderCompleted)
END_EVENT_TABLE()

wxraytracerFrame::wxraytracerFrame(const wxPoint& pos, const wxSize& size)
	: wxFrame(static_cast<wxFrame*>(nullptr), -1, wxT("Ray Tracer"), pos, size) {
	auto* menuFile = new wxMenu;

	menuFile->Append(Menu_File_Open, wxT("&Open..."));
	menuFile->Append(Menu_File_Save, wxT("&Save As..."));
	menuFile->AppendSeparator();
	menuFile->Append(Menu_File_Quit, wxT("E&xit"));

	menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), FALSE);

	auto* menuRender = new wxMenu;

	menuRender->Append(Menu_Render_Start, wxT("&Start"));
	menuRender->Append(Menu_Render_Pause, wxT("&Pause"));
	menuRender->Append(Menu_Render_Resume, wxT("&Resume"));

	menuRender->Enable(menuRender->FindItem(wxT("&Start")), TRUE);
	menuRender->Enable(menuRender->FindItem(wxT("&Pause")), FALSE);
	menuRender->Enable(menuRender->FindItem(wxT("&Resume")), FALSE);

	auto* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuRender, wxT("&Render"));

	SetMenuBar(menuBar);

	canvas = new RenderCanvas(this);

	CreateStatusBar();
	SetStatusText(wxT("Ready"));

	wxIcon icon(main_xpm);
	SetIcon(icon);

	wxStatusBar* statusBar = GetStatusBar();
	int widths[] = {150, 300};
	statusBar->SetFieldsCount(2, widths);
}

void wxraytracerFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
	Close();
}

void wxraytracerFrame::OnSaveFile(wxCommandEvent& WXUNUSED(event)) {
	wxString caption = wxT("Save File");

	wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|"
							"PNG files (*.png)|*.png|"
							"JPEG files (*.jpg)|*.jpg|"
							"TIFF files (*.tif)|*.tif");

	wxString defaultDir = wxEmptyString;
	wxString defaultFilename = wxT("render.bmp");

	wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
						wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	dialog.SetPath(currentPath);

	if (dialog.ShowModal() == wxID_OK) {
		currentPath = dialog.GetPath();

		wxImage theImage = canvas->GetImage();
		theImage.SaveFile(currentPath);
	}
}

void wxraytracerFrame::OnOpenFile(wxCommandEvent& WXUNUSED(event)) {
	wxString caption = wxT("Choose a file");

	wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|"
							"PNG files (*.png)|*.png|"
							"JPEG files (*.jpg)|*.jpg|"
							"TIFF files (*.tif)|*.tif");

	wxString defaultDir = wxEmptyString;
	wxString defaultFilename = wxEmptyString;

	wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
						wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	dialog.SetPath(currentPath);

	if (dialog.ShowModal() == wxID_OK) {
		currentPath = dialog.GetPath();
		auto* theImage = new wxImage();
		theImage->LoadFile(currentPath);

		if (!theImage->IsOk()) {
			delete theImage;
			wxMessageBox(wxT("Sorry, could not load file."));
		} else {
			canvas->SetImage(*theImage);
			wxMenu* menuFile = GetMenuBar()->GetMenu(0);
			menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), TRUE);
		}
	}
}

void wxraytracerFrame::OnRenderStart(wxCommandEvent& WXUNUSED(event)) {
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Pause")), TRUE);
	menu->Enable(menu->FindItem(wxT("&Resume")), FALSE);

	canvas->renderStart();

	wxMenu* menuFile = GetMenuBar()->GetMenu(0);
	menuFile->Enable(menuFile->FindItem(wxT("&Open...")), FALSE);
	menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), TRUE);
}

void wxraytracerFrame::OnRenderCompleted(wxCommandEvent& event [[maybe_unused]]) {
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), TRUE);
	menu->Enable(menu->FindItem(wxT("&Pause")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Resume")), FALSE);

	wxMenu* menuFile = GetMenuBar()->GetMenu(0);
	menuFile->Enable(menuFile->FindItem(wxT("&Open...")), TRUE);

	wxGetApp().SetStatusText(wxT("Rendering complete"));
}

void wxraytracerFrame::OnRenderPause(wxCommandEvent& event [[maybe_unused]]) {
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Pause")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Resume")), TRUE);

	canvas->renderPause();

	wxGetApp().SetStatusText(wxT("Rendering paused"));
}

void wxraytracerFrame::OnRenderResume(wxCommandEvent& event [[maybe_unused]]) {
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Pause")), TRUE);
	menu->Enable(menu->FindItem(wxT("&Resume")), FALSE);

	canvas->renderResume();

	wxGetApp().SetStatusText(wxT("Rendering..."));
}


/******************************************************************************/
/********************* RenderCanvas *******************************************/
/******************************************************************************/


RenderCanvas::RenderCanvas(wxWindow* parent)
	: wxScrolledWindow(parent), m_image(nullptr), w(nullptr), thread(nullptr),
	  timer(nullptr), updateTimer(this, ID_RENDER_UPDATE) {
	SetOwnBackgroundColour(wxColour(143, 144, 150));
}

RenderCanvas::~RenderCanvas() {
	if (m_image != nullptr)
		delete m_image;

	if (thread != nullptr)
		thread->Delete();

	if (w != nullptr)
		delete w;

	if (timer != nullptr)
		delete timer;
}

void RenderCanvas::SetImage(wxImage& image) {
	if (m_image != nullptr)
		delete m_image;

	m_image = new wxBitmap(image);

	SetScrollbars(10, 10, static_cast<int>(m_image->GetWidth() / 10.0f),
				  static_cast<int>(m_image->GetHeight() / 10.0f), 0, 0, true);

	Refresh();
}

wxImage RenderCanvas::GetImage() {
	if (m_image != nullptr)
		return m_image->ConvertToImage();

	return wxImage();
}

void RenderCanvas::OnDraw(wxDC& dc) {
	if (m_image != nullptr && m_image->IsOk())
		wxBufferedDC bdc(&dc, *m_image);
}

void RenderCanvas::OnRenderCompleted(wxCommandEvent& event [[maybe_unused]]) {
	thread = nullptr;

	if (w != nullptr) {
		delete w;
		w = nullptr;
	}

	if (timer != nullptr) {
		long interval = timer->Time();

		wxTimeSpan timeElapsed(0, 0, 0, interval);
		wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));
		wxGetApp().SetStatusText(timeString, 1);

		delete timer;
		timer = nullptr;
	}
}

void RenderCanvas::OnNewPixel(wxCommandEvent& event) {
	// set up double buffered device context
	wxClientDC cdc(this);
	DoPrepareDC(cdc);
	wxBufferedDC bufferedDC(&cdc, *m_image);

	// iterate over all pixels in the event
	auto* pixelsUpdate =
		static_cast<vector<RenderPixel*>*>(event.GetClientData());

	for (auto itr = pixelsUpdate->begin();
		 itr != pixelsUpdate->end(); itr++) {
		RenderPixel* pixel = *itr;

		wxPen pen(wxColour(pixel->red, pixel->green, pixel->blue));
		bufferedDC.SetPen(pen);
		bufferedDC.DrawPoint(pixel->x, pixel->y);

		pixelsRendered++;
		delete pixel;
	}

	pixelsUpdate->clear();
	delete pixelsUpdate;
}

void RenderCanvas::renderPause() {
	if (thread != nullptr)
		thread->Pause();

	updateTimer.Stop();

	if (timer != nullptr)
		timer->Pause();
}

void RenderCanvas::renderResume() {
	if (thread != nullptr)
		thread->Resume();

	updateTimer.Start();

	if (timer != nullptr)
		timer->Resume();
}

void RenderCanvas::OnTimerUpdate(wxTimerEvent& event [[maybe_unused]]) {
	if (timer == nullptr)
		return;

	// percent
	float completed = static_cast<float>(pixelsRendered) / static_cast<float>(pixelsToRender);

	wxString progressString = wxString::Format(wxT("Rendering...%d%%"),
											   static_cast<int>(completed * 100));
	wxGetApp().SetStatusText(progressString, 0);

	// time elapsed
	long interval = timer->Time();

	wxTimeSpan timeElapsed(0, 0, 0, interval);

	// time remaining
	float remaining = 1.0f - completed;
	long msecRemain = static_cast<long>((static_cast<double>(interval) / (completed * 100)) * 100 * remaining);

	wxTimeSpan timeRemaining(0, 0, 0, msecRemain);

	wxString timeRemainString = timeRemaining.Format(wxT(" / ETA: %H:%M:%S"));
	wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));

	// only display ETA if something has been completed
	if (msecRemain >= 0)
		wxGetApp().SetStatusText(timeString + timeRemainString, 1);
	else
		wxGetApp().SetStatusText(timeString, 1);
}

void RenderCanvas::renderStart() {
	w = new World();

	wxGetApp().SetStatusText(wxT("Building world..."));

	// TODO(fix): builder
	// w->build();

	wxGetApp().SetStatusText(wxT("Rendering..."));

	pixelsRendered = 0;
	pixelsToRender = w->vp.hres * w->vp.vres;

	// set the background
	wxBitmap bitmap(w->vp.hres, w->vp.vres, -1);
	wxMemoryDC dc;
	dc.SelectObject(bitmap);
	dc.SetBackground(*wxGREY_BRUSH);
	dc.Clear();

	wxBitmap tile(bg_xpm);

	for (int x = 0; x < w->vp.hres; x += 16) {
		for (int y = 0; y < w->vp.vres; y += 16)
			dc.DrawBitmap(tile, x, y, FALSE);
	}

	dc.SelectObject(wxNullBitmap);

	wxImage temp = bitmap.ConvertToImage();
	SetImage(temp);

	updateTimer.Start(250);

	// start timer
	timer = new wxStopWatch();

	thread = new RenderThread(this, w);
	thread->Create();
	w->paintArea = thread;
	thread->SetPriority(20);
	thread->Run();
}

/******************************************************************************/
/********************* RenderPixel ********************************************/
/******************************************************************************/


RenderPixel::RenderPixel(int _x, int _y, int _red, int _green, int _blue)
	: x(_x), y(_y), red(_red), green(_green), blue(_blue) {}


/******************************************************************************/
/********************* RenderThread *******************************************/
/******************************************************************************/

DEFINE_EVENT_TYPE(wxEVT_RENDER)

BEGIN_EVENT_TABLE(RenderCanvas, wxScrolledWindow)
EVT_COMMAND(ID_RENDER_NEWPIXEL, wxEVT_RENDER,
			RenderCanvas::OnNewPixel)
EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER,
			RenderCanvas::OnRenderCompleted)
EVT_TIMER(ID_RENDER_UPDATE, RenderCanvas::OnTimerUpdate)
END_EVENT_TABLE()

void RenderThread::setPixel(int x, int y, int redValue, int green, int blue) {
	pixels.push_back(new RenderPixel(x, y, redValue, green, blue));

	if (timer->Time() - lastUpdateTime > 40)
		NotifyCanvas();

	TestDestroy();
}

void RenderThread::NotifyCanvas() {
	lastUpdateTime = timer->Time();

	// copy rendered pixels into a new vector and reset
	auto* pixelsUpdate = new vector<RenderPixel*>(pixels);
	pixels.clear();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_NEWPIXEL);
	event.SetClientData(pixelsUpdate);
	canvas->GetEventHandler()->AddPendingEvent(event);
}

void RenderThread::OnExit() {
	NotifyCanvas();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_COMPLETED);

	canvas->GetEventHandler()->AddPendingEvent(event);

	canvas->GetParent()->GetEventHandler()->AddPendingEvent(event);
}

void* RenderThread::Entry() {
	lastUpdateTime = 0;
	timer = new wxStopWatch();

	// world->render_scene(); //for bare bones ray tracer only
	world->camera_ptr->render_scene(*world);

	return nullptr;
}

void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);

	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);

	int x = column;
	int y = vp.vres - row - 1;

	paintArea->setPixel(x, y, static_cast<int>(mapped_color.r * 255),
						static_cast<int>(mapped_color.g * 255),
						static_cast<int>(mapped_color.b * 255));
}
