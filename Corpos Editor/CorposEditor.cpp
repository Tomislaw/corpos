#include "CorposEditor.h"
#include "game\utility\Logger.hpp"
#include <QStandardItemModel>
#include <QErrorMessage>
std::string CorposEditor::selectedTile = "";
std::string CorposEditor::selectedTileset = "";

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
	if (a == 0)Logger::e("Error in parsing editor executable location");

	// load other parts
	Options::loadIniFile();
	GameAssetsManager::loadTextures(Options::textureLocation);
	GameAssetsManager::loadSprites(Options::spriteLocation);

	optionsForm = new OptionsForms();
	spriteForm = new SpriteBrowser();
	newMapforms = new NewMapForms(this);
	tilesetEditor = new TilesetEditor();
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
		optionsForm->close();
	delete optionsForm;

	//if (spriteForm != nullptr)
	delete spriteForm;

	if (newMapforms != nullptr)
		newMapforms->close();
	delete newMapforms;

	delete tilesetEditor;
}

void CorposEditor::createMap(int sizex, int sizey, std::string name)
{
	this->ui.mdiArea->addSubWindow(new MapForm(this, sizex, sizey, name))->showFullScreen();
}

void CorposEditor::writeConsole(std::string info)
{
	this->ui.consoleText->setText(QString::fromStdString(info) + ui.consoleText->toPlainText());
}

void CorposEditor::showSpriteBrowserForms()
{
	if (spriteForm != nullptr)
		spriteForm->show();
}

void CorposEditor::showTilesetEditor()
{
	if (tilesetEditor != nullptr)
		tilesetEditor->show();
}

void CorposEditor::loadMap()
{
	WCHAR filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = L".txt\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Select a file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		//ui.gameExeLineText->setText(QString::fromStdWString(filename));

		std::wstring ws(filename);
		std::string str(ws.begin(), ws.end());

		this->ui.mdiArea->addSubWindow(new MapForm(this, str))->showFullScreen();
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

void CorposEditor::saveMap()
{
	WCHAR filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = L".txt\0*.exe\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Select a File, yo!";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn))
	{
		//ui.gameExeLineText->setText(QString::fromStdWString(filename));

		std::wstring ws(filename);
		std::string str(ws.begin(), ws.end());

		auto win = dynamic_cast<MapForm*>(windowPtr->widget());
		if (win != nullptr)
		{
			win->saveToFile(str);
			QMessageBox::information(
				this,
				tr("Info"),
				tr(("Map successfuly saved to \"" + str + "\"").c_str()));
		}
		else
		{
			QMessageBox::information(
				this,
				tr("Error"),
				tr("Unable to save file."));
		}
		//this->ui.mdiArea->addSubWindow(new MapForm(this, str));
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

void CorposEditor::newMap()
{
	newMapforms->show();
}

void CorposEditor::loadTileDefinitions(QMdiSubWindow * window)
{
	ui.actionSave->setEnabled(false);
	windowPtr = window;
	if (window == nullptr)return;

	auto win = dynamic_cast<MapForm*>(window->widget());
	if (win != nullptr)
	{
		ui.actionSave->setEnabled(true);
		ui.tileListWidget->clear();

		auto addTile = [](std::shared_ptr<TileDefinition > d, QListWidget * list) {
			//Create main widget
			QWidget *tileWidget = new QWidget;

			//Create tile view
			TileView *view = new TileView(tileWidget, QPoint(), QSize(34, 34));
			view->setTile(d.get());

			//create label name and type
			QLabel * labelName = new QLabel();;
			QLabel * labelType = new QLabel();
			labelName->setAccessibleName("name");
			if (d)
			{
				labelName->setText(QString::fromStdString(d->name));

				if (d->is_blocking == true)labelType->setText("tile");
				else labelType->setText("background");
			}
			else
			{
				labelName->setText("air");
				labelType->setText("background");
			}

			//create label tileset
			QLabel * labelTileset = new QLabel();
			labelTileset->setAccessibleName("tileset");
			labelTileset->setText("default");

			//set layout
			QHBoxLayout *layout = new QHBoxLayout;
			layout->addWidget(view);
			layout->addWidget(labelName);
			layout->addWidget(labelType);
			layout->addWidget(labelTileset);
			tileWidget->setLayout(layout);

			//add item
			QListWidgetItem* item;
			item = new QListWidgetItem(list);
			list->addItem(item);
			item->setSizeHint(tileWidget->minimumSizeHint());
			list->setItemWidget(item, tileWidget);
		};

		addTile( nullptr, ui.tileListWidget);

		for(auto item : win->mapView->world.tilesets[0].tileDefinitions)
			addTile(item, ui.tileListWidget);

		Logger::e(std::to_string(window->size().height()));
	}
	else
	{
		ui.tileListWidget->clear();
	}
}

void CorposEditor::tileSelected(QListWidgetItem *item)
{
	if (item == nullptr)
	{
		selectedTile = "";
		selectedTileset = "";
	}
	else
	{
		auto widget = ui.tileListWidget->itemWidget(item);

		std::string name = "";
		std::string tileset = "";
		for each (QWidget* var in widget->children())
		{
			auto w = dynamic_cast<QLabel *>(var);
			if (w)
			{
				if (w->accessibleName().contains("name"))
				{
					name = w->text().toStdString();
				}
				if (w->accessibleName().contains("tileset"))
				{
					tileset = w->text().toStdString();
				}
			}
		}

		if (name == "")
		{
			Logger::e("Selected tile is invalid!");
			selectedTile = "";
			selectedTileset = "";
		}
		else
		{
			selectedTile = name;
			selectedTileset = tileset;
		}
	}
}

void CorposEditor::tileFilter(QString str)
{
	for (int i = 0; i < ui.tileListWidget->count(); i++)
	{
		QListWidgetItem* item = ui.tileListWidget->item(i);
		auto widget = ui.tileListWidget->itemWidget(item);
		for each (QWidget* var in widget->children())
		{
			auto w = dynamic_cast<QLabel *>(var);
			if (w)
			{
				if (w->accessibleName().contains("name"))
				{
					auto name = w->text().toLower();
					item->setHidden(!name.contains(str.toLower()));
					break;
				}
			}
		}
	}
}

void CorposEditor::updateMenuView()
{
	ui.actionOutput_window->setChecked(ui.consoleDock->isVisible());
	ui.actionTile_browser->setChecked(ui.tileDock->isVisible());
	ui.actionEntity_list->setChecked(ui.entityDock->isVisible());
}