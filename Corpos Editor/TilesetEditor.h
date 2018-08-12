#ifndef TILESET_EDITOR_HPP
#define TILESET_EDITOR_HPP

#include <QWidget>
#include "ui_TilesetEditor.h"
#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "TileView.h"

#include "FrameEditor.h"
	
/*!
	Editor designated to edit files with definition of tileset.
	Suitable for editing tileset definition, tile definition and apperance of these tiles.
*/
class TilesetEditor : public QMainWindow
{
	Q_OBJECT

public:

	/*!
		Main constructor.
		Initializing ui, TileView and FrameEditor here.
		\param parent is parent of this object.
		\sa TileView, TileView
	*/
	TilesetEditor(QWidget *parent = Q_NULLPTR);

	/*! 
		Main deconstructor.
	*/
	~TilesetEditor();

	public slots:
	

	/*!
		Popup load file window.
		Loading tileset from selected file.
	*/
	void loadTileset();

	/*!
		Popup save file window.
		Saving tileset to selected file.
		\sa saveToFile(std::string file)
	*/
	void saveTileset();

	/*!
		Update TileView.
		\sa TileView
	*/
	void updateTileView();

	/*!
		Update TileView.
		\sa TileView
	*/
	void changeTileset();
	
	/*! Reload texture list in combobox_Texture.*/
	void reloadData();

	/*! Reload tile list in treeWidget_Tiles.*/
	void reloadTileDefinitions();

	/*! Set text in lineedit when choosed texture from combobox */
	void selectedTexture(QString);

	/*!
		Load data when selected tile definition.
		Populate treeWidget_tilesGrid with data from selected tile definition
		and set data in groupbox with information of this tile.
	*/
	void onSelectedTileDefinition(QTreeWidgetItem*, int);

	/*!
		Parse data of selected frame to load to FrameEditor.
		\sa FrameEditor.
	*/
	void onSelectedTileFrame(QTreeWidgetItem*, int);


	/*!
		Load data from FrameEditor to this editor.
		\sa FrameEditor.
	*/
	void setFrameData(sf::IntRect);

	/*!
		Update data in FrameEditor.
		\sa FrameEditor.
	*/
	void updateFrameEditorData();

	/*! Replace data in selected frame with given data.*/
	void editFrame();
	/*! Delete selected frame.*/
	void deleteFrame();
	/*! Duplicate selected frame.*/
	void duplicateFrame();
	
	/*! Add frame.*/
	void addFrame();

	/*! Replace data in selected tile with given data.*/
	void editTile();
	/*! Delete selected tile.*/
	void deleteTile();
	/*! Duplicate selected tile.*/
	void duplicateTile();
	/*! Add tile.*/
	void addTile();

private:
	/*!
		Change information of current tileset.
	*/
	void changeTilesetData(std::string name, std::string texture, std::string size);

	/*!
		Add tiledefinition to treewidget
	*/
	void addTile(TextElement * e);

	/*!
		Save tileset data to given location.
		\param location File path to file.

	*/
	void saveToFile(std::string location);

	Ui::TilesetEditor ui;		/*!< Class contains all other ui elements. */

	TileView * tileView;		/*!< Display current selected tile. */
	FrameEditor * frameEdit;	/*!< Display current selected frame of tile. */

	std::string name;			/*!< Name of the tileset. */
	std::string texture;		/*!< Name of texture used in tileset. */


	std::vector<TileDefinition> tileDefinitions; /*!< List of current tile definitions. */

	int selectdTileId = -1;				/*!< Id of current selected tile definition. */
	sf::IntRect selectedRectangle;		/*!< Data of currrent selected frame. */
	int selectetRectangleType = error;	/*!< Selected frame type. */

	/*!
		Enum with all types of frame.
	*/
	enum FrameType {error,Left,Right,Top,Bottom,Center,Inner,InnerRightTop,InnerLeftTop, InnerRightBottom, InnerLeftBottom , LeftTop, RightTop, LeftBottom, RightBottom};

	/*!
		Change string to FrameType enum.
		\param str String to change to enum.
		\sa FrameType
	*/
	int getFrameType(std::string str);

	/*!
		Delete frame from given tile definition.
		Function is looking for exacly the same frame and deletes it.
		\param tile Tile definition to delete from.
		\param rect Frame to search and delete.
		\param type FrameType enum of frame.
		\sa FrameType
	*/
	void deleteFrameFromTile(TileDefinition & tile, sf::IntRect rect, int type);

	/*!
		Add frame to given tile definition.
		Function is adding frame to given tile definition.
		\param tile Tile definition to add frame,
		\param rect Frame to add.
		\param type FrameType enum of frame.
		\sa FrameType
	*/
	void addFrameToTile(TileDefinition & tile, sf::IntRect rect, int type);

	/*!
		Replace frame in given tile definition.
		Function is replacing frame in given tile definition.
		\param tile Tile definition to replace frame,
		\param previous Frame to be replaced.
		\param next Next value of frame.
		\param type FrameType enum of frame.
		\sa FrameType
	*/
	void replaceFrameInTile(TileDefinition & tile, sf::IntRect previous, sf::IntRect next, int type);
};

#endif