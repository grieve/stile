#include "Configurator.h"

struct stile::Configurator::ConfiguratorImpl
{
public:
	Configurator&	mParent;
	Timer&	mTimer;
	Logger&	mLogger;
	char	mConfigFile[256];
	bool	mLastFailed;
	map<string, bool>	mBooleanOptions;
	map<string, string>	mStringOptions;
	map<string, int>	mIntegerOptions;
	map<string, float>	mFloatOptions;

	void	loadConfiguration	();
	void	handleOptionInternally	(const char* option, bool value);
	void	handleOptionInternally	(const char* option, string& value);
	void	handleOptionInternally	(const char* option, int value);
	void	handleOptionInternally	(const char* option, float& value);
	bool	getBooleanOption	(const char* option);
	void	setBooleanOption	(const char* option, bool value);
	string&	getStringOption	(const char* option);
	void	setStringOption	(const char* option, string& value);
	int	getIntegerOption	(const char* option);
	void	setIntegerOption	(const char* option, int value);
	float	getFloatOption	(const char* option);
	void	setFloatOption	(const char* option, float value);

	ConfiguratorImpl	(
			Configurator& parent,
			const char* configFile,
			Timer* timer,
			Logger* logger
		)
		: mParent	(parent)
		, mTimer	(*timer)
		, mLogger	(*logger)
	{
		strcpy (mConfigFile, configFile);
		loadConfiguration ();
		mLastFailed = false;
	};

	~ConfiguratorImpl	()
	{
	}
};

void stile::Configurator::ConfiguratorImpl::loadConfiguration ()
{
	ifstream config (mConfigFile, ifstream::in);
	if (config.fail())
	{
		mLogger.warning("Unable to load configuration file \"%s\".", mConfigFile);
		return;
	}
	string	optionString;
	string	keyString;
	string	valueString;
	int	valueInt;
	float	valueFloat;
	int	equalsPos;

	while (getline(config, optionString))
	{
		if (optionString.length() == 0)
		{
			continue;
		}
		optionString	= optionString.substr(optionString.find_first_not_of(" "));
		if (optionString.c_str()[0]=='#')
		{
			//commented line - print at debug level 5 otherwise skip
			if (optionString.length() > 1)
			{
				mLogger.debug(5, "Configuration comment: %s", optionString.substr(1).c_str());
			}
			continue;
		}
		equalsPos	= optionString.find_first_of("=");
		keyString	= optionString.substr(0, equalsPos);
		valueString	= optionString.substr(equalsPos+1);
		if (valueString == "true")
		{
			handleOptionInternally (keyString.c_str(), true);
			setBooleanOption(keyString.c_str(), true);
		}
		else
		{
			if (valueString == "false")
			{
				handleOptionInternally (keyString.c_str(), false);
				setBooleanOption(keyString.c_str(), false);
			}
			else
			{
				if (valueString.find_first_not_of("0123456789.") < 1024)
				{
					handleOptionInternally (keyString.c_str(), valueString);
					setStringOption(keyString.c_str(), valueString);
				}
				else
				{
					if (valueString.find_first_of('.') < 1024)
					{
						valueFloat = atof(valueString.c_str());
						handleOptionInternally (keyString.c_str(), valueFloat);
						setFloatOption(keyString.c_str(), valueFloat);
					}
					else
					{
						valueInt = atoi(valueString.c_str());
						handleOptionInternally (keyString.c_str(), valueInt);
						setIntegerOption(keyString.c_str(), valueInt);
					}
				}
			}
		}
	}
}

void stile::Configurator::ConfiguratorImpl::handleOptionInternally	(
		const char* option,
		bool value
	)
{
	if (strcmp(option,"enableStdOut")==0)
	{
		mLogger.enableStdOut(value);
	}
}

void stile::Configurator::ConfiguratorImpl::handleOptionInternally	(
		const char* option,
		string& value
	)
{
}

void stile::Configurator::ConfiguratorImpl::handleOptionInternally	(
		const char* option,
		int value
	)
{
	if (strcmp(option,"debugLevel")==0)
	{
		mLogger.setDebugLevel(value);
	}
}

void stile::Configurator::ConfiguratorImpl::handleOptionInternally	(
		const char* option,
		float& value
	)
{
}

stile::Configurator::Configurator	(
		const char* configFile,
		Timer* timer,
		Logger* logger
	)
	: mImpl(*new ConfiguratorImpl(*this, configFile, timer, logger))
{
}

stile::Configurator::~Configurator()
{
}

void stile::Configurator::loadConfiguration ()
{
	mImpl.loadConfiguration();
}

void stile::Configurator::saveConfiguration ()
{
}

bool stile::Configurator::ConfiguratorImpl::getBooleanOption	(
		const char* option
	)
{
	map<string,bool>::iterator iter = mBooleanOptions.find(option);
	if (iter == mBooleanOptions.end())
	{
		mLogger.warning("Boolean option \"%s\" not found.", option);
		mLastFailed = true;
	}
	else
	{
		return iter->second;
		mLastFailed = false;
	}
}

void stile::Configurator::ConfiguratorImpl::setBooleanOption	(
		const char* option,
		bool value
	)
{
	map<string,bool>::iterator iter = mBooleanOptions.find(option);
	if (iter == mBooleanOptions.end())
	{
		mBooleanOptions.insert(map<string,bool>::value_type(option, value));
	}
	else
	{
		(iter->second) = value;
	}
}

string& stile::Configurator::ConfiguratorImpl::getStringOption	(
		const char* option
	)
{
	map<string,string>::iterator iter = mStringOptions.find(option);
	if (iter == mStringOptions.end())
	{
		mLogger.warning("String option \"%s\" not found.", option);
		mLastFailed = true;
	}
	else
	{
		return iter->second;
		mLastFailed = false;
	}
}

void stile::Configurator::ConfiguratorImpl::setStringOption	(
		const char* option,
		string& value
	)
{
	map<string,string>::iterator iter = mStringOptions.find(option);
	if (iter == mStringOptions.end())
	{
		mStringOptions.insert(map<string,string>::value_type(option, value));
	}
	else
	{
		(iter->second) = value;
	}
}

int stile::Configurator::ConfiguratorImpl::getIntegerOption	(
		const char* option
	)
{
	map<string, int>::iterator iter = mIntegerOptions.find(option);
	if (iter == mIntegerOptions.end())
	{
		mLogger.warning("Integer option \"%s\" not found.", option);
		mLastFailed = true;
	}
	else
	{
		return iter->second;
		mLastFailed = false;
	}
}

void stile::Configurator::ConfiguratorImpl::setIntegerOption	(
		const char* option,
		int value
	)
{
	map<string, int>::iterator iter = mIntegerOptions.find(option);
	if (iter == mIntegerOptions.end())
	{
		mIntegerOptions.insert(map<string, int>::value_type(option, value));
	}
	else
	{
		(iter->second) = value;
	}
}

float stile::Configurator::ConfiguratorImpl::getFloatOption	(
		const char* option
	)
{
	map<string, float>::iterator iter = mFloatOptions.find(option);
	if (iter == mFloatOptions.end())
	{
		mLogger.warning("Float option \"%s\" not found.", option);
		mLastFailed = true;
	}
	else
	{
		return iter->second;
		mLastFailed = false;
	}
}

void stile::Configurator::ConfiguratorImpl::setFloatOption	(
		const char* option,
		float value
	)
{
	map<string, float>::iterator iter = mFloatOptions.find(option);
	if (iter == mFloatOptions.end())
	{
		mFloatOptions.insert(map<string, float>::value_type(option, value));
	}
	else
	{
		(iter->second) = value;
	}
}

bool stile::Configurator::getBooleanOption	(
		const char* option
	)
{
	return mImpl.getBooleanOption(option);
}

void stile::Configurator::setBooleanOption	(
		const char* option,
		bool value
	)
{
	mImpl.setBooleanOption(option, value);
}

string& stile::Configurator::getStringOption	(
		const char* option
	)
{
	return mImpl.getStringOption(option);
}

void stile::Configurator::setStringOption	(
		const char* option,
		string& value
	)
{
	mImpl.setStringOption(option, value);
}

int stile::Configurator::getIntegerOption	(
		const char* option
	)
{
	return mImpl.getIntegerOption(option);
}

void stile::Configurator::setIntegerOption	(
		const char* option,
		int value
	)
{
	mImpl.setIntegerOption(option, value);
}

float stile::Configurator::getFloatOption	(
		const char* option
	)
{
	return mImpl.getFloatOption(option);
}

void stile::Configurator::setFloatOption	(
		const char* option,
		float value
	)
{
	mImpl.setFloatOption (option, value);
}

bool stile::Configurator::fail ()
{
	return mImpl.mLastFailed;
}
