#ifndef FPGASOC_READ_HPP
#define FPGASOC_READ_HPP

#include <ostream>
#include <boost/program_options.hpp>

#include <fpgasoc_cmd.hpp>

#define FPGASOC_READ_CMD_NAME "read"

namespace util_fpgasoc {

class ReadFnct : public CmdFnct {
	public:
		ReadFnct(std::ostream &ost, std::ostream &est) noexcept(true);

		bool operator()(int argc, const char * const * const argv) noexcept(true) override;

	private:
		void _printHelp(bool isError = false) const noexcept(true) override;
		boost::program_options::options_description _opdesc;
};

} // End of "namespace util_fpgasoc"

#endif

