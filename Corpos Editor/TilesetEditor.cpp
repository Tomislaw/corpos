#include "TilesetEditor.h"

TilesetEditor::TilesetEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	tileView = new TileView(ui.frameTileView, QPoint(), QSize(200, 200));
	tileView->setViewSize(0.37);
	tileView->view.setCenter(sf::Vector2f(34, 34));

	frameEdit = new FrameEditor(nullptr, QPoint(), QSize(1000, 1000));
	ui.verticalLayout_TextureView->addWidget(frameEdit);
	frameEdit->setViewSize(0.32);
	reloadData();
	setMouseTracking(frameEdit);

	QObject::connect(frameEdit, &FrameEditor::frameChanged,
		this, &TilesetEditor::setFrameData);
}

TilesetEditor::~TilesetEditor()
{
	delete tileView;
}

void TilesetEditor::onSelectedTileDefinition(QTreeWidgetItem * item, int)
{
	//clear treewidget with frames
	if (!item)
	{
		selectdTileId = -1;
		ui.treeWidget_tilesGrid->clear();
		return;
	}

	selectdTileId = ui.treeWidget_Tiles->indexOfTopLevelItem(item);
	if (selectdTileId == -1)return;

	//load tileview;
	if (tileView)tileView->setTile(&tileDefinitions[selectdTileId]);
	updateTileView();
	//tileView->setViewSize(1.1);
	auto tiledefinition = tileDefinitions[selectdTileId];

	//load data to items
	{
		ui.lineEdit_tileName->setText(QString::fromStdString(tiledefinition.name));
		ui.lineEdit_background->setText(QString::fromStdString(tiledefinition.backgroundTile));
		ui.lineEdit_connectGroup->setText(QString::fromStdString(tiledefinition.connectGroup));
		ui.spinBox_health->setValue(tiledefinition.health);

		if (tiledefinition.is_blocking)
		{
			int index = ui.comboBox_tileType->findData("tile", Qt::DisplayRole);
			ui.comboBox_tileType->setCurrentIndex(index);
		}
		else
		{
			int index = ui.comboBox_tileType->findData("background", Qt::DisplayRole);
			ui.comboBox_tileType->setCurrentIndex(index);
		}
		ui.checkBox_singleImage->setChecked(tiledefinition.singleImage);
		ui.lineEdit_tileName->setText(QString::fromStdString(tiledefinition.name));
		ui.spinBox_tileRectX->setValue(tiledefinition.tileRect.left);
		ui.spinBox_TilerectY->setValue(tiledefinition.tileRect.top);
		ui.spinBox_TilerectW->setValue(tiledefinition.tileRect.width);
		ui.spinBox_TilerectH->setValue(tiledefinition.tileRect.height);
	}

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
		widget->setText(0, "top-left");
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
		widget->setText(0, "bottom-left");
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
		widget->setText(0, "top-right");
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
		widget->setText(0, "bottom-right");
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
		widget->setText(0, "inner-top-left");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	for each (auto var in tiledefinition.ILB)
	{
		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "inner-bottom-left");
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
		widget->setText(0, "inner-top-right");
		std::string pos = std::to_string(var.left) + "," + std::to_string(var.top);
		std::string size = std::to_string(var.width) + "," + std::to_string(var.height);
		widget->setText(1, QString::fromStdString(pos));
		widget->setText(2, QString::fromStdString(size));

		ui.treeWidget_tilesGrid->addTopLevelItem(widget);
	}
	for each (auto var in tiledefinition.IRB)
	{
		auto widget = new QTreeWidgetItem(ui.treeWidget_tilesGrid);
		widget->setText(0, "inner-bottom-right");
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

void TilesetEditor::updateTileView()
{
	bool a, b, c,
		d,/**/e,
		f, g, h;
	a = ui.checkBox_LeftTop->isChecked();		b = ui.checkBox_Top->isChecked();		c = ui.checkBox_RightTop->isChecked();
	d = ui.checkBox_Left->isChecked();			/* center of tile*/				    	e = ui.checkBox_Right->isChecked();
	f = ui.checkBox_LeftBottom->isChecked();	g = ui.checkBox_Bottom->isChecked();	h = ui.checkBox_RightBottom->isChecked();

	tileView->setTileCollidables(a, b, c, d, e, f, g, h);
	tileView->setViewSize(0.34);
}

void TilesetEditor::changeTileset()
{
	changeTilesetData(ui.lineEdit_tilesetName->text().toStdString(), ui.lineEdit_Texture->text().toStdString(), "");
}

void TilesetEditor::reloadData()
{
	auto textures = GameDataHolder::getInstance()->getTextureList();
	ui.comboBox_Texture->clear();
	for each (auto var in textures)
	{
		ui.comboBox_Texture->addItem(QString::fromStdString(var));
	}
	tileView->update();
}

void TilesetEditor::reloadTileDefinitions()
{
	ui.treeWidget_Tiles->clear();

	for each (auto td in tileDefinitions)
	{
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

	selectdTileId = -1;
	ui.treeWidget_tilesGrid->clear();
}

void TilesetEditor::selectedTexture(QString text)
{
	ui.lineEdit_Texture->setText(text);
}

void TilesetEditor::onSelectedTileFrame(QTreeWidgetItem * item, int)
{
	if (selectdTileId == -1)
	{
		ui.treeWidget_tilesGrid->clear();
		return;
	}
	auto tileDefinition = &tileDefinitions[selectdTileId];

	auto type = item->text(0).toStdString();
	selectetRectangleType = getFrameType(type);

	int index = ui.comboBox_frameType->findData(item->text(0), Qt::DisplayRole);
	ui.comboBox_frameType->setCurrentIndex(index);

	auto pos = item->text(1).toStdString();
	auto size = item->text(2).toStdString();
	int l, t, w, h = 0;
	int center = pos.find_first_of(',');

	auto strL = pos.substr(0, center + 1);
	l = std::atoi(strL.c_str());
	auto strT = pos.substr(center + 1);
	t = std::atoi(strT.c_str());

	center = size.find_first_of(',');
	auto strW = size.substr(0, center + 1);
	w = std::atoi(strW.c_str());
	auto strH = size.substr(center + 1);
	h = std::atoi(strH.c_str());

	selectedRectangle = sf::IntRect(l, t, w, h);
	frameEdit->setFrame(selectedRectangle);
}

void TilesetEditor::setFrameData(sf::IntRect rect)
{
	ui.spinBox_posX->setValue(rect.left);
	ui.spinBox_posY->setValue(rect.top);
	ui.spinBox_sizeX->setValue(rect.width);
	ui.spinBox_sizeY->setValue(rect.height);
}

void TilesetEditor::updateFrameEditorData()
{
	if (frameEdit->isFrameMoving())return;
	int x = ui.spinBox_posX->value();
	int y = ui.spinBox_posY->value();
	int w = ui.spinBox_sizeX->value();
	int h = ui.spinBox_sizeY->value();

	frameEdit->setFrame(sf::IntRect(x, y, w, h));
}

void TilesetEditor::editFrame()
{
	if (selectdTileId == -1)return;

	int type = getFrameType(ui.comboBox_frameType->currentText().toStdString());
	if (type == error)return;

	//add frame
	int x = ui.spinBox_posX->value();
	int y = ui.spinBox_posY->value();
	int w = ui.spinBox_sizeX->value();
	int h = ui.spinBox_sizeY->value();

	//replace element
	if (type == selectetRectangleType)replaceFrameInTile(tileDefinitions[selectdTileId], selectedRectangle, sf::IntRect(x, y, w, h), type);
	else
	{
		deleteFrameFromTile(tileDefinitions[selectdTileId], selectedRectangle, selectetRectangleType);
		addFrameToTile(tileDefinitions[selectdTileId], sf::IntRect(x, y, w, h), type);
	}
	// deselect item
	selectetRectangleType = error;

	//reload tileFrames;
	onSelectedTileDefinition(ui.treeWidget_Tiles->currentItem(), 0);
}

void TilesetEditor::deleteFrame()
{
	if (selectdTileId == -1)return;
	deleteFrameFromTile(tileDefinitions[selectdTileId], selectedRectangle, selectetRectangleType);

	// deselect item
	selectetRectangleType = error;

	//reload tileFrames;
	onSelectedTileDefinition(ui.treeWidget_Tiles->currentItem(), 0);
}

void TilesetEditor::duplicateFrame()
{
	if (selectdTileId == -1)return;
	addFrameToTile(tileDefinitions[selectdTileId], selectedRectangle, selectetRectangleType);

	// deselect item
	selectetRectangleType = error;

	//reload tileFrames;
	onSelectedTileDefinition(ui.treeWidget_Tiles->currentItem(), 0);
}

void TilesetEditor::addFrame()
{
	if (selectdTileId == -1)return;
	int type = getFrameType(ui.comboBox_frameType->currentText().toStdString());
	if (type == error)return;

	//add frame
	int x = ui.spinBox_posX->value();
	int y = ui.spinBox_posY->value();
	int w = ui.spinBox_sizeX->value();
	int h = ui.spinBox_sizeY->value();

	addFrameToTile(tileDefinitions[selectdTileId], sf::IntRect(x, y, w, h), type);

	// deselect item
	selectetRectangleType = error;

	//reload tileFrames;
	onSelectedTileDefinition(ui.treeWidget_Tiles->currentItem(), 0);
}

void TilesetEditor::editTile()
{
	if (selectdTileId == -1)return;

	TileDefinition & tile = tileDefinitions[selectdTileId];

	tile.name = ui.lineEdit_tileName->text().toStdString();
	tile.backgroundTile = ui.lineEdit_background->text().toStdString();
	tile.connectGroup = ui.lineEdit_connectGroup->text().toStdString();
	tile.health = ui.spinBox_health->value();

	if (ui.comboBox_tileType->currentText() == "background")
		tile.is_blocking = false;
	else tile.is_blocking = true;

	tile.singleImage = ui.checkBox_singleImage->isChecked();

	tile.tileRect.left = ui.spinBox_tileRectX->value();
	tile.tileRect.top = ui.spinBox_TilerectY->value();
	tile.tileRect.width = ui.spinBox_TilerectW->value();
	tile.tileRect.height = ui.spinBox_TilerectH->value();

	reloadTileDefinitions();
}

void TilesetEditor::deleteTile()
{
	if (selectdTileId == -1)return;
	tileDefinitions.erase(tileDefinitions.begin() + selectdTileId);

	reloadTileDefinitions();
}

void TilesetEditor::duplicateTile()
{
	if (selectdTileId == -1)return;
	tileDefinitions.push_back(TileDefinition(tileDefinitions[selectdTileId]));

	reloadTileDefinitions();
}

void TilesetEditor::addTile()
{
	TileDefinition tile;

	tile.name = ui.lineEdit_tileName->text().toStdString();
	tile.backgroundTile = ui.lineEdit_background->text().toStdString();
	tile.connectGroup = ui.lineEdit_connectGroup->text().toStdString();
	tile.health = ui.spinBox_health->value();

	if (ui.comboBox_tileType->currentText() == "background")
		tile.is_blocking = false;
	else tile.is_blocking = true;

	tile.singleImage = ui.checkBox_singleImage->isChecked();

	tile.tileRect.left = ui.spinBox_tileRectX->value();
	tile.tileRect.top = ui.spinBox_TilerectY->value();
	tile.tileRect.width = ui.spinBox_TilerectW->value();
	tile.tileRect.height = ui.spinBox_TilerectH->value();

	if (tile.singleImage)
	{
		tile.inner.push_back(sf::IntRect());
	}
	else
	{
		tile.LT.push_back(sf::IntRect()); tile.T.push_back(sf::IntRect()), tile.RT.push_back(sf::IntRect());
		tile.L.push_back(sf::IntRect()); tile.C.push_back(sf::IntRect()), tile.R.push_back(sf::IntRect());
		tile.LB.push_back(sf::IntRect()); tile.B.push_back(sf::IntRect()), tile.RB.push_back(sf::IntRect());

		tile.IRB.push_back(sf::IntRect()); tile.ILB.push_back(sf::IntRect());
		tile.IRT.push_back(sf::IntRect()); tile.ILT.push_back(sf::IntRect());
	}

	tileDefinitions.push_back(tile);
	reloadTileDefinitions();
}

void TilesetEditor::saveTileset()
{
	if (tileDefinitions.size() == 0)
	{
		QMessageBox::information(
			this,
			tr("Error"),
			tr("Nothing to save."));
		return;
	}
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
		saveToFile(str);

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

void TilesetEditor::changeTilesetData(std::string name, std::string texture, std::string size)
{
	this->name = name;
	this->texture = texture;

	ui.label_Name->setText(QString::fromStdString(name));
	ui.label_Texture->setText(QString::fromStdString(texture));

	int index = ui.comboBox_Texture->findData(QString::fromStdString(texture), Qt::DisplayRole);
	ui.comboBox_Texture->setCurrentIndex(index);

	auto tex = GameDataHolder::getInstance()->getTexture(texture);
	for (int i = 0; i < tileDefinitions.size(); i++)
	{
		auto var = &tileDefinitions[i];
		var->textureName = texture;
		var->texture = tex;
	}

	if (!tex)
	{
		auto info = "Texture with name " + texture + "not found";
		QMessageBox::information(
			this,
			tr("Texture not found"),
			tr(info.c_str()));
	}
	else
	{
		if (size == "")
		{
			ui.label_Texturesize->setText(QString::number(tex->getSize().x) + "," + QString::number(tex->getSize().y));
		}
		frameEdit->setTexture(texture);
	}
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

void TilesetEditor::saveToFile(std::string file)
{
	TextFileData fileData;
	TextElement tileset;
	tileset.name = "TILESET";

	Variable tilesetName;
	tilesetName.name = "Name";
	tilesetName.var.push_back(name);
	tileset.variable.push_back(tilesetName);

	Variable tilesetTexture;
	tilesetTexture.name = "Texture";
	tilesetTexture.var.push_back(texture);
	tileset.variable.push_back(tilesetTexture);

	Variable tilesetSize;
	tilesetSize.name = "Texture_size";

	sf::Rect<unsigned> texture_size;
	if (frameEdit->getTexture())texture_size = sf::Rect<unsigned>(sf::Vector2u(), frameEdit->getTexture()->getSize());
	tilesetSize.var.push_back(std::to_string(texture_size.left));
	tilesetSize.var.push_back(std::to_string(texture_size.top));
	tilesetSize.var.push_back(std::to_string(texture_size.width));
	tilesetSize.var.push_back(std::to_string(texture_size.height));
	tileset.variable.push_back(tilesetSize);

	std::vector<TextElement> elements;
	elements.push_back(tileset);

	for each (auto tile in tileDefinitions)
	{
		elements.push_back(tile.generateTextElement());
	}
	fileData.setElements(elements);
	bool saved = fileData.saveToFile(file);

	if (!saved)
		QMessageBox::information(
			this,
			tr("Error"),
			tr("Unable to save file."));
}

int TilesetEditor::getFrameType(std::string type)
{
	int IType;
	if (type == "top") IType = Top;
	else if (type == "bottom") IType = Bottom;
	else if (type == "left") IType = Left;
	else if (type == "right") IType = Right;
	else if (type == "inner") IType = Inner;
	else if (type == "center") IType = Center;
	else if (type == "top-left") IType = LeftTop;
	else if (type == "bottom-left") IType = LeftBottom;
	else if (type == "top-right") IType = RightTop;
	else if (type == "bottom-right") IType = RightBottom;
	else if (type == "inner-top-left") IType = InnerLeftTop;
	else if (type == "inner-bottom-left") IType = InnerLeftBottom;
	else if (type == "inner-top-right") IType = InnerRightTop;
	else if (type == "inner-bottom-right") IType = InnerRightBottom;
	else IType = error;
	return IType;
}

void TilesetEditor::deleteFrameFromTile(TileDefinition & tile, sf::IntRect rect, int type)
{
	auto deleteFrame = [](std::vector<sf::IntRect>&vec, sf::IntRect rect)->bool
	{ 	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == rect)
		{
			vec.erase(vec.begin() + i);
			return true;
		}
	}
	return false;
	};

	switch (type)
	{
	case Left:
		deleteFrame(tile.L, rect);
		break;
	case Right:
		deleteFrame(tile.R, rect);
		break;
	case Top:
		deleteFrame(tile.T, rect);
		break;
	case Bottom:
		deleteFrame(tile.B, rect);
		break;
	case LeftTop:
		deleteFrame(tile.LT, rect);
		break;
	case LeftBottom:
		deleteFrame(tile.LB, rect);
		break;
	case RightTop:
		deleteFrame(tile.RT, rect);
		break;
	case RightBottom:
		deleteFrame(tile.RB, rect);
		break;
	case Inner:
		deleteFrame(tile.inner, rect);
		break;
	case Center:
		deleteFrame(tile.C, rect);
		break;
	case InnerLeftBottom:
		deleteFrame(tile.ILB, rect);
		break;
	case InnerLeftTop:
		deleteFrame(tile.ILT, rect);
		break;
	case InnerRightBottom:
		deleteFrame(tile.IRB, rect);
		break;
	case InnerRightTop:
		deleteFrame(tile.IRT, rect);
		break;
	default:

		break;
	}
}

void TilesetEditor::addFrameToTile(TileDefinition & tile, sf::IntRect rect, int type)
{
	switch (type)
	{
	case Left:
		tile.L.push_back(rect);
		break;
	case Right:
		tile.R.push_back(rect);
		break;
	case Top:
		tile.T.push_back(rect);
		break;
	case Bottom:
		tile.B.push_back(rect);
		break;
	case LeftTop:
		tile.LT.push_back(rect);
		break;
	case LeftBottom:
		tile.LB.push_back(rect);
		break;
	case RightTop:
		tile.RT.push_back(rect);
		break;
	case RightBottom:
		tile.RB.push_back(rect);
		break;
	case Inner:
		tile.inner.push_back(rect);
		break;
	case Center:
		tile.C.push_back(rect);
		break;
	case InnerLeftBottom:
		tile.ILB.push_back(rect);
		break;
	case InnerLeftTop:
		tile.ILT.push_back(rect);
		break;
	case InnerRightBottom:
		tile.IRB.push_back(rect);
		break;
	case InnerRightTop:
		tile.IRT.push_back(rect);
		break;
	default:
		break;
	}
}

void TilesetEditor::replaceFrameInTile(TileDefinition & tile, sf::IntRect previous, sf::IntRect next, int type)
{
	auto editFrame = [](std::vector<sf::IntRect>&vec, sf::IntRect rect, sf::IntRect rect2)->bool
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == rect)
			{
				vec[i] = rect2;
				return true;
			}
		}
		return false;
	};

	switch (type)
	{
	case Left:
		editFrame(tile.L, previous, next);
		break;
	case Right:
		editFrame(tile.R, previous, next);
		break;
	case Top:
		editFrame(tile.T, previous, next);
		break;
	case Bottom:
		editFrame(tile.B, previous, next);
		break;
	case LeftTop:
		editFrame(tile.LT, previous, next);
		break;
	case LeftBottom:
		editFrame(tile.LB, previous, next);
		break;
	case RightTop:
		editFrame(tile.RT, previous, next);
		break;
	case RightBottom:
		editFrame(tile.RB, previous, next);
		break;
	case Inner:
		editFrame(tile.inner, previous, next);
		break;
	case Center:
		editFrame(tile.C, previous, next);
		break;
	case InnerLeftBottom:
		editFrame(tile.ILB, previous, next);
		break;
	case InnerLeftTop:
		editFrame(tile.ILT, previous, next);
		break;
	case InnerRightBottom:
		editFrame(tile.IRB, previous, next);
		break;
	case InnerRightTop:
		editFrame(tile.IRT, previous, next);
		break;
	default:
		break;
	}
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
				if (n)
				{
					name = n->toString(0);
					ui.lineEdit_tilesetName->setText(n->toString(0).c_str());
				}

				auto t = tilesetData->getVariableByName("Texture");
				if (t)
				{
					texture = t->toString(0);
					ui.lineEdit_Texture->setText(t->toString(0).c_str());
				}

				changeTilesetData(name, texture, "");
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