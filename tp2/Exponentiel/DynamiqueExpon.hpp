#ifndef __DYNAMIQUEEXPON_HPP__
#define __DYNAMIQUEEXPON_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal2d.hpp>

class DynamiqueExpon : public plugin
{
private:
// Donnees en entree
	auto_ref<ns_wtni::GrayImage> input;
// Donnees en sortie
	auto_ref<ns_wtni::GrayImage> output;
// Parametres
	int n;
	bool raise;

	bool verifyParameters(std::string &msg, bool isRunning);

public:
	DynamiqueExpon( pluglink * p );

	bool is_n_set( std::string &msg );
	bool is_raise_set( std::string &msg );

	virtual bool is_ready( std::string & );

	virtual bool execute( std::string & );
};

#endif
