#ifndef __DIVRESOLUTION_HPP__
#define __DIVRESOLUTION_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal2d.hpp>

class DivResolution : public plugin
{
private:
    // Donnees en entree
        const_auto_ref<ns_wtni::GrayImage> input;
    // Donnees en sortie
        auto_ref<ns_wtni::GrayImage> output;
// Parametres
	int n_x;
	int n_y;

	bool verifyParameters(std::string &msg, bool isRunning);

public:
	DivResolution( pluglink * p );

	bool is_n_x_set( std::string &msg );
	bool is_n_y_set( std::string &msg );

	virtual bool is_ready( std::string & );

	virtual bool execute( std::string & );
};

#endif
