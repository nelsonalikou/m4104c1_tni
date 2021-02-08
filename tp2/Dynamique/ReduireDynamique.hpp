#ifndef __REDUIREDYNAMIQUE_HPP__
#define __REDUIREDYNAMIQUE_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal2d.hpp>

class ReduireDynamique : public plugin
{
private:
// Donnees en entree
	auto_ref<ns_wtni::GrayImage> input;
// Donnees en sortie
	auto_ref<ns_wtni::GrayImage> output;
// Parametres
	int d;

	bool verifyParameters(std::string &msg, bool isRunning);

public:
	ReduireDynamique( pluglink * p );

	bool is_d_set( std::string &msg );

	virtual bool is_ready( std::string & );

	virtual bool execute( std::string & );
};

#endif
