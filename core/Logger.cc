/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/


#include "Logger.h"

struct stile::Logger::LoggerImpl
{
public:
	Logger&	mParent;
	Timer&	mTimer;
	char	mInternalBuffer[4096];
	char	mFormattedTime[13];
	float*	mElapsedTime;
	unsigned int	mDebugLevel;
	bool	mStdOut;

	std::vector<OutputHandler*>	mOutputHandlers;
	std::vector<OutputCallback>	mOutputCallbacks;

	LoggerImpl	(
			Logger& parent,
			const char* name,
			Timer* timer
		)
		: mParent	(parent)
		, mTimer	(*timer)
	{
		mDebugLevel	= 0;
		mStdOut	= false;
	};
	~LoggerImpl	(){};

	void write	(const char* prefix, const char* output);
};

void stile::Logger::LoggerImpl::write	(
		const char* prefix,
		const char* output
	)
{
	char formattedTime[16];
	sprintf (formattedTime, "%.3f", mTimer.getSeconds());
	std::ostringstream strOutput;
	strOutput <<"(" << formattedTime << ") " << prefix << ": " <<output << std::endl;
	if (mStdOut)
	{
		std::cout << strOutput.str();
	}

		for (unsigned int x=0; x< mOutputHandlers.size(); x++)
		{
			mOutputHandlers[x]->write(strOutput);
		}

		for (unsigned int x=0; x< mOutputCallbacks.size(); x++)
		{
			mOutputCallbacks[x](strOutput);
		}

}

stile::Logger::Logger	(
		const char* name,
		stile::Timer* timer
	)
	: mImpl (*new LoggerImpl(*this, name, timer))
{
}

stile::Logger::~Logger ()
{
}

void stile::Logger::setDebugLevel	(
		unsigned int level
	)
{
	mImpl.mDebugLevel = level;
	debug(level, "Debug level changed.");
}

void stile::Logger::enableStdOut	(
		bool enable
	)
{
	mImpl.mStdOut = enable;
	if (enable)
	{
		debug(1,"Standard out has been enabled.");
	}
	else
	{
		debug(1,"Standard out has been disabled.");
	}
}

void stile::Logger::addOutputCallback	(
		stile::OutputCallback cb
	)
{
	for (unsigned int x=0;x<mImpl.mOutputCallbacks.size();x++)
	{
		if (mImpl.mOutputCallbacks[x] == cb)
		{
			warning("Logger: Output callback already added: 0x%x", cb);
			return;
		}
	}
	mImpl.mOutputCallbacks.push_back(cb);
	debug(3, "Logger: Output callback added: 0x%x", cb);
}
void stile::Logger::removeOutputCallback	(
		stile::OutputCallback cb
	)
{
	for (unsigned int x=0;x<mImpl.mOutputCallbacks.size();x++)
	{
		if (mImpl.mOutputCallbacks[x] == cb)
		{
			mImpl.mOutputCallbacks.erase(mImpl.mOutputCallbacks.begin()+x);
			debug(3, "Logger: Output callback removed: 0x%x", cb);
			return;
		}
	}
	warning("Logger: Cannot remove output callback: 0x%x", cb);
}

void stile::Logger::addOutputListener	(
		stile::OutputHandler* listener
	)
{
	for (unsigned int x=0;x<mImpl.mOutputHandlers.size();x++)
	{
		if (mImpl.mOutputHandlers[x] == listener)
		{
			warning("Logger: Output listener already added: 0x%x", listener);
			return;
		}
	}
	mImpl.mOutputHandlers.push_back(listener);
	debug(3, "Logger: Output listener added: 0x%x", listener);
}

void stile::Logger::removeOutputListener	(
		stile::OutputHandler* listener
	)
{
	for (unsigned int x=0;x<mImpl.mOutputHandlers.size();x++)
	{
		if (mImpl.mOutputHandlers[x] == listener)
		{
			mImpl.mOutputHandlers.erase(mImpl.mOutputHandlers.begin()+x);
			debug(3, "Logger: Output listener removed: 0x%x", listener);
			return;
		}
	}
	warning("Logger: Cannot remove output listener: 0x%x", listener);
}

void stile::Logger::error	(
		const char* format,
		...
	)
{
	va_list vl;
	va_start (vl, format);
	vsprintf(mImpl.mInternalBuffer, format, vl);
	va_end(vl);

	mImpl.write("ERROR", mImpl.mInternalBuffer);
}

void stile::Logger::warning	(
		const char* format,
		...
	)
{
	va_list vl;
	va_start (vl, format);
	vsprintf(mImpl.mInternalBuffer, format, vl);
	va_end(vl);

	mImpl.write("WARNING", mImpl.mInternalBuffer);
}

void stile::Logger::info	(
		const char* format,
		...
	)
{
	va_list vl;
	va_start (vl, format);
	vsprintf(mImpl.mInternalBuffer, format, vl);
	va_end(vl);

	mImpl.write("INFO", mImpl.mInternalBuffer);
}

void stile::Logger::debug	(
		unsigned int level,
		const char* format,
		...
	)
{
	if (level > mImpl.mDebugLevel)
		return;

	va_list vl;
	va_start (vl, format);
	vsprintf(mImpl.mInternalBuffer, format, vl);
	va_end(vl);
	char prefix[9];
	sprintf(prefix,"DEBUG[%d]", level);
	mImpl.write(prefix, mImpl.mInternalBuffer);
}
