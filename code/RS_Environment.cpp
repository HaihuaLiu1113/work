#include "RS_Environment.h"

void RS_Environment::writeConfig_()
{
	pugi::xml_document d;
	pugi::xml_node root = d.append_child("RoomServer");
	root.append_attribute("version") = ROOMSERVER_VERSION;
	root.append_attribute("autor") = ROOMSERVER_AUTHOR;
	root.append_attribute("lastdate") = ROOMSERVER_LASTDATE;

	pugi::xml_node RSConfig = root.append_child("RSConfig");
	RSConfig.append_attribute("port") = "5188";

	pugi::xml_node DBConfig = root.append_child("DBConfig");
	DBConfig.append_attribute("DBUser") = "root";
	DBConfig.append_attribute("DBPassword") = "123";

	d.save_file(path_.c_str());
}

bool RS_Environment::readConfig_()
{
	pugi::xml_document d;
	if (!d.load_file(path_.c_str()))
	{
		return false;
	}
	pugi::xml_node root = d.child("RoomServer");
	config_.version = root.attribute("version").as_string();
	config_.author = root.attribute("autor").as_string();
	config_.lastdate = root.attribute("lastdate").as_string();

	pugi::xml_node RSConfig = root.child("RSConfig");
	config_.port = RSConfig.attribute("port").as_int();

	pugi::xml_node DBConfig = root.child("DBConfig");
	config_.DBUser = DBConfig.attribute("DBUser").as_string();
	config_.DBPassword = DBConfig.attribute("DBPassword").as_string();

	return true;
}

bool RS_Environment::init()
{
	if (!readConfig_())
	{
		writeConfig_();
		return false;
	}
	return true;	
}

