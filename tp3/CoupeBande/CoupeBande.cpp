#include "CoupeBande.hpp"

using namespace ns_wtni;

CoupeBande::CoupeBande( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
	add_input( input, "signal d'entree" );

// Ajout des donnees en sortie
	add_output( output, "signal de sortie" );
// Ajout des parametres
    n1 = 0;
	add_param( n1, "indice1" );
    n2 = 0;
	add_param( n2, "indice2" );
}


bool CoupeBande::is_n1_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre n1
    if(n1 < 0){
        // Renseigner la variable msg si necessaire
        msg = "l'indice doit etre positif";
        return false;
    }
	return true; 
}

bool CoupeBande::is_n2_set( std::string &msg )
{
	// Ajouter les tests a faire sur le parametre n2
    if(n2 < 0){
        // Renseigner la variable msg si necessaire
        msg = "l'indice doit etre positif";
        return false;
    }
	return true; 
}

bool CoupeBande::verifyParameters( std::string &msg, bool isRunning )
{
	//Tableau contenant les differents messages
	std::vector<std::string> msgs;
	std::string _msg; // Message local
	bool res = true;
	_msg.clear();
	if ( is_param_input( &n1 )==isRunning && ! is_n1_set( _msg ) )
	{
		 res = false;
		 msgs.push_back( _msg );
	}
	_msg.clear();
	if ( is_param_input( &n2 )==isRunning && ! is_n2_set( _msg ) )
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

bool CoupeBande::is_ready( std::string & msg )
{
	return verifyParameters(msg, false);
}

bool CoupeBande::execute( std::string &msg)
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
    output = new ns_wtni::e1::signal<double>(input->size());
    for(unsigned int pos=0; pos < output->size(); pos++){
        int dif = abs(n1 - n2);
        int start = n1;
        if(n1 > n2){
            start = n2;
        }
        if(pos > (unsigned int)start && pos < (unsigned int)(start + dif)){
            //mise à zero des cases dont l'indice est compris entre n1 et n2
            (*output)[pos] = 0;
        }
        //annulation des coefficients compris entre N-n1 et N-n2
        if(pos > output->size()-start && pos < (output->size()-start +dif)){
            (*output)[pos] = 0;
        }
    }
	return true; 
}

CREATE_PLUGIN( CoupeBande );

