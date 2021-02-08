#ifndef __EGALISEHISTO_HPP__
#define __EGALISEHISTO_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal2d.hpp>

class EgaliseHisto : public plugin
{
private:
// Donnees en entree
	auto_ref<ns_wtni::GrayImage> input;
// Donnees en sortie
	auto_ref<ns_wtni::GrayImage> output;
// Parametres

public:
	EgaliseHisto( pluglink * p );

	virtual bool execute( std::string & );
};

#endif
