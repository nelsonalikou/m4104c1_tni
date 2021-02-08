#include "ReduireDynamique.hpp"

using namespace ns_wtni;

ReduireDynamique::ReduireDynamique( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
	add_input( input, "image en entree" );

// Ajout des donnees en sortie
	add_output( output, "image de sortie" );
// Ajout des parametres
	d = 7;
	add_param( d, "Dynamique de l'image" );
}


bool ReduireDynamique::is_d_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre d
	// Renseigner la variable msg si necessaire
    if (this->d < 0 || this->d > 7)
    {
        msg = "la dynamique doit etre comprise entre 0 et 8";
        return false;
    }
	return true; 
}

bool ReduireDynamique::verifyParameters( std::string &msg, bool isRunning )
{
	//Tableau contenant les differents messages
	std::vector<std::string> msgs;
	std::string _msg; // Message local
	bool res = true;
	_msg.clear();
	if ( is_param_input( &d )==isRunning && ! is_d_set( _msg ) )
	{
		 res = false;
		 msgs.push_back( _msg );
	}
	if ( msgs.size()==1 ) msg = msgs.front();
	else if ( msgs.size()>1 )
	{
		msg = "<ul>";
		for (unsigned int i=0; i<msgs.size(); ++i)
			msg += "<li>" + msgs[i] + "</li>";
		msg += "</ul>";
	}
	return res;
}

bool ReduireDynamique::is_ready( std::string & msg )
{
	return verifyParameters(msg, false);
}

bool ReduireDynamique::execute( std::string &msg)
{
	//Tester les parametres
	if ( !verifyParameters( msg, true ) ) 
		return false;

	// Tester les entrees - A COMPLETER si NECESSAIRE !
	if ( ! input )
	{
		 msg = "L'entree n°1 n'est pas initialisee.";
		return false;
	}

    output = input;
    // ALLOUER les sorties ! TODO
	// Ecrire le code du plugin : TODO !!

    // Réduction de la dynamique en utilisant indifféremment
    // input ou output puisque les deux référencient
    // la même image...
    GrayImage &out = *output;

    //int masque = 255 - (2^(8-d)-1);
    //int masque = 1 << (8-d);

    for (unsigned int colonne = 0; colonne < input->width(); colonne++) {
        // afficher un pixel sur n_x (ici 2)

            for (unsigned int ligne = 0; ligne < input->height(); ligne++) {
                // afficher un pixel sur n_y (ici 2)
                    //std::cout << "avant " << output->pixel(colonne,ligne);
               int  newPixel =  out[ligne][colonne] >> (8-d);
               //newPixel << (8-d);
               out[ligne][colonne] = newPixel << (8-d);
               //out[ligne][colonne] = (out[ligne][colonne] >> (8-d)) << (8-d);
               //out[ligne][colonne] = out[ligne][colonne] & masque;
        }

    }

	return true; 
}

CREATE_PLUGIN( ReduireDynamique );

