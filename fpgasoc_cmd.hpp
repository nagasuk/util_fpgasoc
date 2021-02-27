#ifndef FPGASOC_CMD_HPP
#define FPGASOC_CMD_HPP

#include <string>
#include <ostream>

// Namespace declaration start
namespace util_fpgasoc {

class CmdFnct {
	public:
		CmdFnct(std::ostream &ost, std::ostream &est) noexcept(true) : _ost(ost), _est(est) {};
		virtual ~CmdFnct() {};
		virtual bool operator()(int argc, const char * const * const argv) = 0;

		static void setProgInfo(const std::string &progName, const std::string &version) noexcept(true);

	protected:
		std::ostream &_outSel(bool isStdError = false) const noexcept(true);
		virtual void _printHelp(bool isError = false) const noexcept(true);
		void _printError(const std::string &msg) const noexcept(true);
		const std::string &_getProgName() const noexcept(true);
		const std::string &_getVersion() const noexcept(true);

	private:
		std::ostream &_ost;
		std::ostream &_est;
		static std::string _progName;
		static std::string _version;
};

} // End of "namespace util_fpgasoc"

#endif
