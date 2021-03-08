#ifndef __SINUSOIDE_HPP__
#define __SINUSOIDE_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal1d.hpp>

class Sinusoide : public plugin
{
private:
// Donnees en entree
// Donnees en sortie
	auto_ref<ns_wtni::e1::signal<double> > output;
// Parametres
	double f1;
	double f2;
	int N;

	bool verifyParameters(std::string &msg, bool isRunning);

public:
	Sinusoide( pluglink * p );

	bool is_f1_set( std::string &msg );
	bool is_f2_set( std::string &msg );
	bool is_N_set( std::string &msg );

	virtual bool is_ready( std::string & );

	virtual bool execute( std::string & );
};

#endif
