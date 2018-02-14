#include "TilesetEditor.h"

TilesetEditor::TilesetEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	TileView * tv = new TileView(ui.frameTileView,QPoint(),QSize(200,200));
}

TilesetEditor::~TilesetEditor()
{
}

void TilesetEditor::loadTileGrid(QTreeWidgetItem * item, int)
{
	
	auto id = ui.treeWidget_Tiles->indexOfTopLevelItem(item);
	if (id == -1)return;
	auto tiledefinition = tileDefinitions.at(id);

	ui.treeWidget_tilesGrid->clear();

	//left
	for each (auto var in tiledefinition.L)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "left");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//top
	for each (auto var in tiledefinition.T)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "top");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//right
	for each (auto var in tiledefinition.R)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "right");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//bottom
	for each (auto var in tiledefinition.B)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "bottom");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//inner
	for each (auto var in tiledefinition.inner)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "inner");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//left-top
	for each (auto var in tiledefinition.LT)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "left-top");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//left - bottom
	for each (auto var in tiledefinition.LB)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "left");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//right-top
	for each (auto var in tiledefinition.RT)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "right-top");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//right-bottom
	for each (auto var in tiledefinition.RB)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "right-bottom");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//
	for each (auto var in tiledefinition.ILT)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "inner-left-top");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	for each (auto var in tiledefinition.ILB)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "inner-left-bottom");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	//
	for each (auto var in tiledefinition.IRT)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "inner-right-top");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	for each (auto var in tiledefinition.IRT)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "inner-right-bottom");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	for each (auto var in tiledefinition.C)
	{

		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "center");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}

}

void TilesetEditor::changeTilesetData(std::string name, std::string texture, std::string size)
{
	this->name = name;
	this->texture = texture;

	ui.label_Name->setText( QString::fromStdString(name));
	ui.label_Texture->setText(QString::fromStdString(texture));
}

void TilesetEditor::addTile(TextElement * e)
{
	auto td = TileDefinition();
	td.setTile(e, nullptr, texture);
	tileDefinitions.push_back(td);



	auto widget = new QTreeWidgetItem(ui.treeWidget_Tiles);
	widget->setText(0, QString::fromStdString(td.name));
	if (td.is_blocking)widget->setText(1, "tile");
	else widget->setText(1, "background");
	widget->setText(2, QString::fromStdString(td.backgroundTile));
	widget->setText(3, QString::fromStdString(std::to_string(td.health)));
	if (td.singleImage)widget->setText(4, "true");
	else widget->setText(4, "false");

	ui.treeWidget_Tiles->addTopLevelItem(widget);
}

void TilesetEditor::loadTileset()
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

		// file operations;
		{
			TextFileData file;
			bool loaded = file.loadFile(str);
			
			if (!loaded)
			{
				Logger::e("Can't open file " + str);
				return;
			}
			auto tilesetData = file.getFirstElementByName("TILESET");
			if (tilesetData == nullptr)
			{
				Logger::e("Tileset data not found");
			}
			else
			{
				auto n = tilesetData->getVariableByName("Name");
				if (n)name = n->toString(0);

				auto t = tilesetData->getVariableByName("Texture");
				if (t)texture = t->toString(0);

				changeTilesetData(name, texture,"");
			}

			auto definitions = file.getAllElementsByName("TILE");

			ui.treeWidget_Tiles->clear();
			tileDefinitions.clear();
			for each (auto tile in definitions)
			{

				addTile(tile);

			}
		}
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
