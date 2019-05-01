#include "json-utils.h"

using namespace corpos;
std::string json_utils::localDiretory = "";

namespace fs = std::filesystem;

json json_utils::from_file(std::string directory)
{
	std::string strDirectory;

	fs::path path = directory;
	fs::path local = localDiretory;
	if (path.is_relative())
		strDirectory = (local.make_preferred() / path.make_preferred()).string();
	else
		strDirectory = path.string();
	try {
		std::ifstream stream(strDirectory);
		json data;
		stream >> data;
		stream.close();
		return data;
	}
	catch (const std::exception& exception)
	{
		Logger::e("Unable to load json from file: {}, cause", strDirectory, std::string(exception.what()));
	}
	return json();
}

void json_utils::to_file(json & data, std::string directory)
{
	try
	{
		std::ofstream(localDiretory + "/" + directory) << data;
	}
	catch (const std::exception& exception)
	{
		Logger::e("Unable to save json to file: {}, cause: ", localDiretory + "/" + directory, std::string(exception.what()));
	}
}