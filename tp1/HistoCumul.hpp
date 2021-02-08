#ifndef __HISTOCUMUL_HPP__
#define __HISTOCUMUL_HPP__

#include <string>

#include <plugin.hpp>
#include <w_signal1d.hpp>
#include <w_signal2d.hpp>

class HistoCumul : public plugin
{
private:
// Donnees en entree
	auto_ref<ns_wtni::GrayImage> input;
// Donnees en sortie
	auto_ref<ns_wtni::e1::signal<long> > histo;
// Parametres

public:
	HistoCumul( pluglink * p );

	virtual bool execute( std::string & );
};

#endif
