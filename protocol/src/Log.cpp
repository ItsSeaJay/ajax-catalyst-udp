#include "Log.h"

AjaxCatalyst::Log::Log()
{}

AjaxCatalyst::Log::~Log()
{}

void AjaxCatalyst::Log::start()
{
	mFile.open(mFilename);
}

void AjaxCatalyst::Log::stop()
{
	mFile.close();
}