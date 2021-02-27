#include <iostream>
#include <sstream>
#include <memory>
#include <unordered_map>
#include <cstring>

#include "fpgasoc_version.hpp"
#include "fpgasoc_cmd.hpp"
#include <fpgasoc_read.hpp>
#include <fpgasoc_write.hpp>


// Settings namespace
using std::string;
using std::unique_ptr;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;

using CommandPointer = unique_ptr<util_fpgasoc::CmdFnct>;
using CommandTable   = std::unordered_map<string, CommandPointer>;

// Macros
#define FPGASOC_RETCODE_OK ((int)0)
#define FPGASOC_RETCODE_NG ((int)1)

// Enum class
enum class ArgStatus {
	valid,
	invalid,
	help
};

// Static objects
static CommandTable cmdTbl;
static string execName;

// Internal functions prototypes
static void initCommandTable();
static ArgStatus analArg(int argc, const char * const * const argv);
static string generateHelp();
static void printError(const string &msg);

// Implementation
int main(int argc, const char * const * const argv)
{
	int retVal = FPGASOC_RETCODE_NG;
	ArgStatus astat;

	initCommandTable();

	astat = analArg(argc, argv);

	if (astat == ArgStatus::valid) {
		bool isCmdSuccess;
		util_fpgasoc::CmdFnct &cmd = *(cmdTbl[argv[1]]);

		isCmdSuccess = cmd((argc - (int)1), &(argv[1]));

		if (isCmdSuccess) {
			retVal = FPGASOC_RETCODE_OK;
		}

	} else if (astat == ArgStatus::help) {
		cout << generateHelp();
		retVal = FPGASOC_RETCODE_OK;

	} else {
		printError("Invalid arguments.");
	}


	return retVal;
}

// Internal functions
static void initCommandTable()
{
	cmdTbl.emplace(FPGASOC_READ_CMD_NAME,  new util_fpgasoc::ReadFnct(cout, cerr));
	cmdTbl.emplace(FPGASOC_WRITE_CMD_NAME, new util_fpgasoc::WriteFnct(cout, cerr));
}

static ArgStatus analArg(int argc, const char * const * const argv)
{
	ArgStatus retVal = ArgStatus::invalid;

	execName = argv[0];

	util_fpgasoc::CmdFnct::setProgInfo(execName, util_fpgasoc::version);

	if (argc > (int)1) {
		if (cmdTbl.find(argv[1]) != cmdTbl.end()) {
			retVal = ArgStatus::valid;
		} else if (strcmp(argv[1], "help") == (int)0) {
			retVal = ArgStatus::help;
		}
	}

	return retVal;
}

static string generateHelp()
{
	stringstream ss;

	ss << '`' << execName << "' Ver. " << util_fpgasoc::version << '\n'
	   << '\n'
	   << "Usage:\n"
	   << " $ " << execName << " <Command>\n"
	   << '\n'
	   << "Commands List:\n";

	for (auto &cpair : cmdTbl) {
		const string &cmdname = cpair.first;
		ss << " - " << cmdname << "\n";
	}

	ss << '\n'
	   << "If you'd like to understand details about various commands,\n"
	   << "type as follows and execute it.\n"
	   << " $ " << execName << " <Command> [--help|-h]\n"
	   << endl;

	return ss.str();
}

static void printError(const string &msg)
{
	cerr << "[Error] " << msg << endl;
	cerr << generateHelp() << endl;
}

