#include "DivResolution.hpp"

using namespace ns_wtni;

DivResolution::DivResolution( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
    add_input( input, "Image d'entree" );
// Ajout des donnees en sortie
    add_output( output, "Image de sortie" );
// Ajout des parametres
    n_x = 2;
    add_param( n_x, "Facteur de division sur les colonnes" );
    n_y = 2;
    add_param( n_y, "Facteur de division sur les lignes" );
}


bool DivResolution::is_n_x_set( std::string &msg )
{
    if (this->n_x < 2)
    {
        msg = "n_x mal initialisé !";
        return false;
    }
    return true;
}

bool DivResolution::is_n_y_set( std::string &msg )
{
    if (this->n_y < 2)
    {
        msg = "n_y mal initialisé !";
        return false;
    }
    return true;
}

bool DivResolution::verifyParameters( std::string &msg, bool isRunning )
{
    //Tableau contenant les differents messages
    std::vector<std::string> msgs;
    std::string _msg; // Message local
    bool res = true;
    _msg.clear();
    if ( is_param_input( &n_x )==isRunning && ! is_n_x_set( _msg ) )
    {
         res = false;
         msgs.push_back( _msg );
    }
    _msg.clear();
    if ( is_param_input( &n_y )==isRunning && ! is_n_y_set( _msg ) )
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

bool DivResolution::is_ready( std::string & msg )
{
    return verifyParameters(msg, false);
}

bool DivResolution::execute( std::string &msg)
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
    output = new GrayImage(input->width() / n_x, input->height() / n_y);
    GrayImage &out = *output;
    const GrayImage &in = *input;

    // Ecrire le code du plugin : TODO !!
    for (unsigned int colonne = 0; colonne < input->width(); colonne++) {
        // afficher un pixel sur n_x (ici 2)
        if(colonne % n_x == 0){
            for (unsigned int ligne = 0; ligne < input->height(); ligne++) {
                // afficher un pixel sur n_y (ici 2)
                if(ligne % n_y == 0 ) {
                    //std::cout << "avant " << output->pixel(colonne,ligne);
                    out[ligne/n_x][colonne/n_y] = in[ligne][colonne];
                }
            }
        }

    }

    return true;
}

CREATE_PLUGIN( DivResolution );

