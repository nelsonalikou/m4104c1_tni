#ifndef __COUPEBANDE_HPP__
#define __COUPEBANDE_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal1d.hpp>

class CoupeBande : public plugin
{
private:
// Donnees en entree
	auto_ref<ns_wtni::e1::signal<double> > input;
// Donnees en sortie
	auto_ref<ns_wtni::e1::signal<double> > output;
// Parametres
    int n1;
    int n2;

	bool verifyParameters(std::string &msg, bool isRunning);

public:
	CoupeBande( pluglink * p );

	bool is_n1_set( std::string &msg );
	bool is_n2_set( std::string &msg );

	virtual bool is_ready( std::string & );

	virtual bool execute( std::string & );
};

#endif
