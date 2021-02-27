#include <ostream>
#include <string>

#include "fpgasoc_cmd.hpp"

using std::ostream;
using std::string;
using std::endl;

namespace util_fpgasoc {

// Static members of class CmdFnct
string CmdFnct::_progName = "";
string CmdFnct::_version = "";

void CmdFnct::setProgInfo(const string &progName, const string &version) noexcept(true)
{
	CmdFnct::_progName = progName;
	CmdFnct::_version  = version;
}

// Protected members of class CmdFnct
void CmdFnct::_printHelp(bool isError) const noexcept(true)
{
	this->_outSel(isError) << '`' << this->_getProgName() << "' Ver. " << this->_getVersion() << '\n' << endl;
}

void CmdFnct::_printError(const string &msg) const noexcept(true)
{
	this->_outSel(true) << "[Error] " << msg << '\n' << endl;
	this->_printHelp(true);
}

ostream &CmdFnct::_outSel(bool isStdError) const noexcept(true)
{
	if (!isStdError) {
		return this->_ost;
	} else {
		return this->_est;
	}
}

const string &CmdFnct::_getProgName() const noexcept(true)
{
	return CmdFnct::_progName;
}

const string &CmdFnct::_getVersion() const noexcept(true)
{
	return CmdFnct::_version;
}

} // End of "namespace util_fpgasoc"

