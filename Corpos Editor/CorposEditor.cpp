#include "CorposEditor.h"
#include "game\utility\Logger.hpp"
#include "GameDataHolder.h"

CorposEditor::CorposEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Logger::getInstance().callback = std::bind(&CorposEditor::writeConsole, this, std::placeholders::_1);
	
	std::string loc = QCoreApplication::applicationFilePath().toStdString();
	// parse exe location
	auto a = loc.find_last_of("\\");
	if (std::string::npos == a)a = 0;
	auto b = loc.find_last_of("/");
	if (std::string::npos == b)b = 0;
	if (b > a)a = b;
	loc.erase(a, loc.size() - a);
	Options::editorExeLocation = loc + "/";
	//
	if(a==0)Logger::e("Error in parsing editor executable location");


	// load other parts
	Options::loadIniFile();
	GameDataHolder::getInstance()->loadTextures();
	GameDataHolder::getInstance()->loadSprites();

	optionsForm = new OptionsForms();
	spriteForm = new SpriteBrowser();
	//connect(ui.actionOptions, SIGNAL(triggered()), this, SLOT(showOptionsForms()));

	//ui.mdiArea->addSubWindow();
}

void CorposEditor::showOptionsForms()
{
	if (optionsForm != nullptr)
	optionsForm->show();
}

CorposEditor::~CorposEditor()
{
	if (optionsForm != nullptr)
	delete optionsForm;
	if (spriteForm != nullptr)
		delete spriteForm;
}

void CorposEditor::writeConsole(std::string info)
{
	this->ui.consoleText->setText(QString::fromStdString(info)+ui.consoleText->toPlainText());
}

void CorposEditor::showSpriteBrowserForms()
{
	if (spriteForm != nullptr)
		spriteForm->show();
}

void CorposEditor::loadMap()
{
	WCHAR filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = L".exe\0*.exe\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Select a File, yo!";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		//ui.gameExeLineText->setText(QString::fromStdWString(filename));

		std::wstring ws(filename);
		std::string str(ws.begin(), ws.end());

		this->ui.mdiArea->addSubWindow(new MapForm(this, str));
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above. 
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}
}
