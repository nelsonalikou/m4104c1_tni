#include "DynamiqueExpon.hpp"

using namespace ns_wtni;

DynamiqueExpon::DynamiqueExpon( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
	add_input( input, "Image d'entree en niveau de gris" );

// Ajout des donnees en sortie
	add_output( output, "image de sortie en niveau de gris" );
// Ajout des parametres
    n = 1;
	add_param( n, "puissance" );
	raise = true;
	add_param( raise, "rehaussement contraste" );
}


bool DynamiqueExpon::is_n_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre n
	// Renseigner la variable msg si necessaire
    if(n < 1){
        msg = "la puissance doit etre positive et non nulle";
        return false;
    }

	return true; 
}

bool DynamiqueExpon::is_raise_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre raise
	// Renseigner la variable msg si necessaire
    if(raise != true && raise != false){
        msg = "booléen mal défini";
        return false;
    }
	return true; 
}

bool DynamiqueExpon::verifyParameters( std::string &msg, bool isRunning )
{
	//Tableau contenant les differents messages
	std::vector<std::string> msgs;
	std::string _msg; // Message local
	bool res = true;
	_msg.clear();
	if ( is_param_input( &n )==isRunning && ! is_n_set( _msg ) )
	{
		 res = false;
		 msgs.push_back( _msg );
	}
	_msg.clear();
	if ( is_param_input( &raise )==isRunning && ! is_raise_set( _msg ) )
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

bool DynamiqueExpon::is_ready( std::string & msg )
{
	return verifyParameters(msg, false);
}

bool DynamiqueExpon::execute( std::string &msg)
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

	// ALLOUER les sorties ! TODO
	// Ecrire le code du plugin : TODO !!
    output = input;
    GrayImage &out = *output;

    for (unsigned int colonne = 0; colonne < input->width(); colonne++) {
            for (unsigned int ligne = 0; ligne < input->height(); ligne++) {
               int pixel = out[ligne][colonne];
                if(raise){
                    //std::cout << pixel << "  " << raise << "  " << round(pow(((double)pixel/(double)255), (double)n) * 255) << std::endl;
                   //pow prend en paramètre des doubles et non des int d'où la necessité de cast avant de reconvertir vers un int
                   out[ligne][colonne] = (int) round(pow(((double)pixel/(double)255), (double)n) * 255);
                }else{
                   //std::cout << pixel << "  " << raise << "  " << pow((pixel/255), 1/n) * 255 << std::endl;
                   out[ligne][colonne] = (int) round(pow(((double)pixel/(double)255), 1/n) * 255);
                }
        }

    }
	return true; 
}

CREATE_PLUGIN( DynamiqueExpon );

