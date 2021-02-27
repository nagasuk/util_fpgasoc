#include <ostream>
#include <string>
#include <boost/program_options.hpp>
#include <libfpgasoc.hpp>

#include <fpgasoc_cmd.hpp>
#include "fpgasoc_write.hpp"

namespace bpo = boost::program_options;
using std::ostream;
using std::endl;
using std::string;

namespace util_fpgasoc {

// Constructors
WriteFnct::WriteFnct(ostream &ost, ostream &est) noexcept(true)
	: CmdFnct::CmdFnct(ost, est), _opdesc("Command \"" FPGASOC_WRITE_CMD_NAME "\" Options")
{
	this->_opdesc.add_options()
		("byte,b",                                     "Switch 1byte-length-write mode. You MUST select only one from '-b', '-w' and '-l'.")
		("word,w",                                     "Switch 2bytes-length-write mode. You MUST select only one from '-b', '-w' and '-l'.")
		("long,l",                                     "Switch 4bytes-length-write mode. You MUST select only one from '-b', '-w' and '-l'.")
		("offset,o", bpo::value<string>()->required(), "Address offset to write. (Base: 0xFF200000) [MUST]")
		("data,d",   bpo::value<string>()->required(), "Data to write.                              [MUST]")
		("help,h",                                     "Show this message.")
		;
}

void WriteFnct::_printHelp(bool isError) const noexcept(true)
{
	CmdFnct::_printHelp(isError);

	this->_outSel(isError) << "Command \"" FPGASOC_WRITE_CMD_NAME "\" Usage:\n"
	                       << " $ " << this->_getProgName() << " " FPGASOC_WRITE_CMD_NAME " <Options>\n"
	                       << '\n'
	                       << this->_opdesc << endl;
}

bool WriteFnct::operator()(int argc, const char * const * const argv) noexcept(true)
{
	// Parse command line options
	bool retVal = false;
	bpo::variables_map vm;

	try {
		bpo::store(bpo::parse_command_line(argc, argv, this->_opdesc), vm);
		bpo::notify(vm);

		if (vm.count("help")) {
			this->_printHelp();
			retVal = true;

		} else if (vm.count("byte") | vm.count("word") | vm.count("long")) {
			Fpgasoc fsobj;

			if (fsobj.isActivated()) {
				const uint32_t offset = (uint32_t)stoul(vm["offset"].as<string>(), nullptr, 0);
				const uint32_t wdata  = (uint32_t)stoul(vm["data"].as<string>(), nullptr, 0);

				if (vm.count("byte")) {
					fsobj.write8(offset, (uint8_t)wdata);
					retVal = true;

				} else if (vm.count("word")) {
					fsobj.write16(offset, (uint16_t)wdata);
					retVal = true;

				} else if (vm.count("long")) {
					fsobj.write32(offset, wdata);
					retVal = true;

				} else { /* Do nothing */ }

			} else {
				this->_printError("Fail to open driver.");
			}

		} else {
			this->_printError("Do NOT select any switch among '-b', '-w' and '-l'.");
		}

	} catch (const bpo::required_option &e) {
		this->_printError(e.what());

	} catch (const bpo::error_with_option_name &e) {
		this->_printError(e.what());

	} catch (const std::invalid_argument &e) {
		this->_printError(e.what());

	} catch (const std::out_of_range &e) {
		this->_printError(e.what());

	} catch (const std::range_error &e) {
		this->_printError(e.what());
	}

	return retVal;
}

} // End of "namespace util_fpgasoc"

