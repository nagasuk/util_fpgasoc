#include <ostream>
#include <iomanip>
#include <bitset>
#include <string>
#include <boost/program_options.hpp>
#include <libfpgasoc.hpp>

#include <fpgasoc_cmd.hpp>
#include "fpgasoc_read.hpp"

namespace bpo = boost::program_options;
using std::ostream;
using std::showbase;
using std::noshowbase;
using std::uppercase;
using std::setw;
using std::setfill;
using std::bitset;
using std::oct;
using std::dec;
using std::hex;
using std::resetiosflags;
using std::endl;
using std::string;

namespace util_fpgasoc {

// Constructors
ReadFnct::ReadFnct(ostream &ost, ostream &est) noexcept(true)
	: CmdFnct::CmdFnct(ost, est), _opdesc("Command \"" FPGASOC_READ_CMD_NAME "\" Options")
{
	this->_opdesc.add_options()
		("byte,b",                                                  "Switch 1byte-length-read mode. You MUST select only one from '-b', '-w' and '-l'.")
		("word,w",                                                  "Switch 2bytes-length-read mode. You MUST select only one from '-b', '-w' and '-l'.")
		("long,l",                                                  "Switch 4bytes-length-read mode. You MUST select only one from '-b', '-w' and '-l'.")
		("offset,o", bpo::value<string>()->required(),              "Address offset to read. (Base: 0xFF200000) [MUST]")
		("format,f", bpo::value<unsigned int>()->default_value(16), "Set the radix of the read result. You can select one from 2, 8, 10 and 16.")
		("help,h",                                                  "Show this message.")
		;
}

void ReadFnct::_printHelp(bool isError) const noexcept(true)
{
	CmdFnct::_printHelp(isError);

	this->_outSel(isError) << "Command \"" FPGASOC_READ_CMD_NAME "\" Usage:\n"
	                       << " $ " << this->_getProgName() << " " FPGASOC_READ_CMD_NAME " <Options>\n"
	                       << '\n'
	                       << this->_opdesc << endl;
}

bool ReadFnct::operator()(int argc, const char * const * const argv) noexcept(true)
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
				const unsigned int &radix = vm["format"].as<unsigned int>();
				uint32_t rdata = (uint32_t)0UL;
				unsigned int bytes = (unsigned int)0U;

				if (vm.count("byte")) {
					rdata = (uint32_t)fsobj.read8(offset);
					bytes = (unsigned int)1U;
					retVal = true;

				} else if (vm.count("word")) {
					rdata = (uint32_t)fsobj.read16(offset);
					bytes = (unsigned int)2U;
					retVal = true;

				} else if (vm.count("long")) {
					rdata = fsobj.read32(offset);
					bytes = (unsigned int)4U;
					retVal = true;

				} else { /* Do nothing */ }

				if (radix == (unsigned int)2U) {
					this->_outSel() << "0b";
					for (unsigned int i = 0; i < bytes; i++) {
						this->_outSel() << bitset<8>((uint8_t)(rdata >> (8*(bytes-i-1))));
					}

				} else if (radix == (unsigned int)8U) {
					this->_outSel() << '0';
					this->_outSel() << oct << setw(4*bytes) << setfill('0') << rdata;

				} else if (radix == (unsigned int)10U) {
					this->_outSel() << rdata;

				} else { // This means radix is 16.
					this->_outSel() << "0x";
					this->_outSel() << hex << setw(2*bytes) << setfill('0') << uppercase << rdata;
				}

				this->_outSel() << resetiosflags(std::ios_base::floatfield) << endl;

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

