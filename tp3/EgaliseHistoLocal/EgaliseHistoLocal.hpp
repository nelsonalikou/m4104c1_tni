#ifndef __EGALISEHISTOLOCAL_HPP__
#define __EGALISEHISTOLOCAL_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal2d.hpp>

class EgaliseHistoLocal : public plugin
{
private:
// Donnees en entree
	const_auto_ref<ns_wtni::GrayImage> input;
// Donnees en sortie
	auto_ref<ns_wtni::GrayImage> output;
// Parametres
	int windowsSize;

	bool verifyParameters(std::string &msg, bool isRunning);

public:
	EgaliseHistoLocal( pluglink * p );

	bool is_windowsSize_set( std::string &msg );

	virtual bool is_ready( std::string & );

	virtual bool execute( std::string & );
};

#endif
