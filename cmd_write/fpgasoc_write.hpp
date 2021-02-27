#ifndef FPGASOC_WRITE_HPP
#define FPGASOC_WRITE_HPP

#include <ostream>
#include <boost/program_options.hpp>

#include <fpgasoc_cmd.hpp>

#define FPGASOC_WRITE_CMD_NAME "write"

namespace util_fpgasoc {

class WriteFnct : public CmdFnct {
	public:
		WriteFnct(std::ostream &ost, std::ostream &est) noexcept(true);

		bool operator()(int argc, const char * const * const argv) noexcept(true) override;

	private:
		void _printHelp(bool isError = false) const noexcept(true) override;
		boost::program_options::options_description _opdesc;
};

} // End of "namespace util_fpgasoc"

#endif

