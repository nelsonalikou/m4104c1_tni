#ifndef __DYNAMIQUELINEAIRE_HPP__
#define __DYNAMIQUELINEAIRE_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal2d.hpp>

class DynamiqueLineaire : public plugin
{
private:
// Donnees en entree
	auto_ref<ns_wtni::GrayImage> input;
// Donnees en sortie
	auto_ref<ns_wtni::GrayImage> output;
// Parametres
	int a;
	int b;
	bool is_heightenable;

	bool verifyParameters(std::string &msg, bool isRunning);

public:
    DynamiqueLineaire( pluglink * p );

	bool is_a_set( std::string &msg );
	bool is_b_set( std::string &msg );
	bool is_is_heightenable_set( std::string &msg );

	virtual bool is_ready( std::string & );

	virtual bool execute( std::string & );
};

#endif
