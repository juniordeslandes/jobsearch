<?php


/**
 * This html class takes the html content from the different job alert
 * emails as input and parses the html based on the job alert type in order to
 * output single offers in the output.html file.
 *
 * @author Maison
 */

use Symfony\Component\DomCrawler\Crawler;

class html {

static function TravailCanada($html)
{
    $crawler = new Crawler($html);
    $contenu_html = "";
    $crawler = $crawler->filter('[style="border: 1px solid #CCC;padding: 0 5px"]');  //capter toutes les lignes dans le tableau des postes affiches
    
    $counter = 0;
    $handle = fopen("jobs.html", "a"); //open output file in append mode
    fwrite($handle, '<!DOCTYPE html><html><head>');
    fwrite($handle, '<meta http-equiv="content-type" content="text/html;charset=utf-8" />');
    fwrite($handle, '</head><body>');
    
    foreach ($crawler as $domElement) 
    {
        $contenu_html .= $domElement->ownerDocument->saveHTML($domElement);
        $element_text = trim($domElement->nodeValue);
        if ($counter == 0)
        {
            fwrite($handle, '<h3>');
        }
         if ($counter == 1)
        {
            Html::TCrequests($domElement);
        }
        if ($counter < 2)
        {
            fwrite($handle, $element_text . '    ->    ');
        }
        if ($counter == 2)
        {
            fwrite($handle, $element_text . '</h3>');
        }
        if ($counter == 3)
        {
            fwrite($handle, $element_text . '<br>');
        }
        if ($counter > 3)
        {
            fwrite($handle, '<br>');
            fwrite($handle, '<hr>');
            fwrite($handle, '<br>');
            $counter = -1;
        }
        $counter++;
        }
//    fwrite($handle, '</body></html>');
    fclose($handle);
} 

static function Indeed()
{

    
}

static function Jobillico()
{

    
}

static function AmeqEnLigne()
{

    
}

static function GroupePerspective()
{

    
}

static function Workopolis()
{

    
}

static function Jobboom()
{

    
}

/*
 * Cette fonction fait ce qui suit:
 * 1. va chercher l'URL de la page intermediaire sur gouv.ca
 * 2. ouvre la page trouvee en 1. ;
 * 3. va chercher l'URL de la page d'Emploi-Qc sur la page intermediaire
 * 4. appelle le traitement de la page d'Emploi-Quebec.
 */
static function TCrequests($domElement)
{
    $a = $domElement->firstChild;  // la balise a est la 
                                  //1re sous le 2e td d'un tr donne
    $href = $a->getAttribute('href'); //aller chercher URL
    $handle = fopen($href, "r"); //ouverture du flux

}
}
