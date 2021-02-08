#include "DynamiqueLineaire.hpp"

using namespace ns_wtni;

DynamiqueLineaire::DynamiqueLineaire( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
	add_input( input, "Image en niveau de gris" );

// Ajout des donnees en sortie
	add_output( output, "Image en niveau de gris" );
// Ajout des parametres
	a = 0;
    add_param( a, "borne inférieure" );
	b = 255;
    add_param( b, "borne supérieure" );
	is_heightenable = true;
	add_param( is_heightenable, "possibilite de rehaussement" );
}


bool DynamiqueLineaire::is_a_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre a
    if(a < 0 || a >= b){
        msg = "a va de 0 à b - 1";
        return false;
    }
	// Renseigner la variable msg si necessaire
	return true; 
}

bool DynamiqueLineaire::is_b_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre b
    if(b < a || b > 255){
        msg = "b va de a+1 à 255";
        return false;
    }
	// Renseigner la variable msg si necessaire
	return true; 
}

bool DynamiqueLineaire::is_is_heightenable_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre is_heightenable
    if(is_heightenable != true && is_heightenable != false){
        msg = "booléen mal défini";
        return false;
    }
	// Renseigner la variable msg si necessaire
	return true; 
}

bool DynamiqueLineaire::verifyParameters( std::string &msg, bool isRunning )
{
	//Tableau contenant les differents messages
	std::vector<std::string> msgs;
	std::string _msg; // Message local
	bool res = true;
	_msg.clear();
	if ( is_param_input( &a )==isRunning && ! is_a_set( _msg ) )
	{
		 res = false;
		 msgs.push_back( _msg );
	}
	_msg.clear();
	if ( is_param_input( &b )==isRunning && ! is_b_set( _msg ) )
	{
		 res = false;
		 msgs.push_back( _msg );
	}
	_msg.clear();
	if ( is_param_input( &is_heightenable )==isRunning && ! is_is_heightenable_set( _msg ) )
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

bool DynamiqueLineaire::is_ready( std::string & msg )
{
	return verifyParameters(msg, false);
}

bool DynamiqueLineaire::execute( std::string &msg)
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
                if(is_heightenable){
                    if(pixel < a){
                        out[ligne][colonne] = 0;
                    }else if(pixel >= a && pixel <= b){
                        out[ligne][colonne] = (pixel-a) * (255/(b-a));
                    }
                    else if(b < pixel){
                        out[ligne][colonne] = 255;
                    }

                }else{
                    out[ligne][colonne] = pixel * (b-a)/255 + a;
                }
        }

    }




	return true; 
}

CREATE_PLUGIN( DynamiqueLineaire );

