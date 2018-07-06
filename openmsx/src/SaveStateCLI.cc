// $Id: SaveStateCLI.cc 12628 2012-06-14 20:15:37Z m9710797 $

#include "SaveStateCLI.hh"
#include "CommandLineParser.hh"
#include "GlobalCommandController.hh"
#include "MSXException.hh"
#include "TclObject.hh"

using std::deque;
using std::string;

namespace openmsx {

SaveStateCLI::SaveStateCLI(CommandLineParser& commandLineParser)
	: commandController(commandLineParser.getGlobalCommandController())
{
	commandLineParser.registerOption("-savestate", *this);
	commandLineParser.registerFileClass("openMSX savestate", *this);
}

bool SaveStateCLI::parseOption(const string& option, deque<string>& cmdLine)
{
	parseFileType(getArgument(option, cmdLine), cmdLine);
	return true;
}

string_ref SaveStateCLI::optionHelp() const
{
	return "Load savestate and start emulation from there";
}

void SaveStateCLI::parseFileType(const string& filename,
                                      deque<string>& /*cmdLine*/)
{
	// TODO: this is basically a C++ version of a part of savestate.tcl.
	// Can that be improved?
	TclObject command(commandController.getInterpreter());
	command.addListElement("restore_machine");
	command.addListElement(filename);
	string newId = command.executeCommand();
	command = TclObject(commandController.getInterpreter());
	command.addListElement("machine");
	string currentId = command.executeCommand();
	if (currentId != "") {
		command = TclObject(commandController.getInterpreter());
		command.addListElement("delete_machine");
		command.addListElement(currentId);
		command.executeCommand();
	}
	command = TclObject(commandController.getInterpreter());
	command.addListElement("activate_machine");
	command.addListElement(newId);
	command.executeCommand();
}

string_ref SaveStateCLI::fileTypeHelp() const
{
	return "openMSX savestate";
}

} // namespace openmsx
