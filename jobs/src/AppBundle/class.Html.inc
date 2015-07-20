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
    
    //capter toutes les lignes dans le tableau des postes affiches
    $crawler = $crawler->filter('[style="border: 1px solid #CCC;padding: 0 5px"]');  
 
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

static function Workopolis($html)
{
    //preparer le fichier html de l'output
    $handle = fopen("jobs.html", "a"); //open output file in append mode
    fwrite($handle, '<!DOCTYPE html><html><head>');
    fwrite($handle, '<meta http-equiv="content-type" content="text/html;charset=utf-8" />');
    fwrite($handle, '</head><body>');
    
    
    $crawler = new Crawler($html);
    
    //capter toutes les balises a qui contiennent un lien vers une page d'offre d'emploi
    $crawler = $crawler->filter('tr > td > a');
    dump($crawler);

    //looper au travers de toutes les offres dans le courriel
    foreach ($crawler as $domElement) 
    {
        //aller chercher URL de la page de l'offre d'emploi
        $href = $domElement->getAttribute('href'); 
        dump($href);
        
        //ouvrir flux de lecture sur la page de l'offre d'emploi
        $handlejobadd = fopen($href, "r");
    
        //jobdesc contient tout le contenu de l'offre
        $jobdesc = '';
        
        //lire le contenu de la page de l'offre et
        //placer le contenu dans $jobdesc
        while (!feof($handlejobadd)) 
        {
            //ajouter a la variable output le contenu de la page d'offre 
            $jobdesc .= fread($handlejobadd, 8192); 
        }        
                
        //creer nouveau crawler pour le titre de l'offre
        $crawler_jobtitle = new Crawler($html);
        $crawler_jobtitle = $crawler_jobtitle->filter('h1');
        
        foreach ($crawler_jobtitle as $domElement) 
        {
            $jobtitle = trim($domElement->nodeValue);
        }
        
        fwrite($handle, '<h1>' . $jobtitle . '</h1>');
        fwrite($handle, $jobdesc);
        fwrite($handle, '<br><br>');
        
    }
     
    //fermer le flux sur cette page d'offre
    fclose($handle);
//    fwrite($handle, '</body></html>');
    
    
}

static function Jobboom()
{

    
}

/*
 * Cette fonction fait ce qui suit:
 * 1. va chercher l'URL de la page intermediaire sur gouv.ca
 * 2. lit la page trouvee en 1. ;
 * 3. va chercher l'URL de la page d'Emploi-Qc sur la page intermediaire
 * 4. appelle le traitement de la page d'Emploi-Quebec.
 */
static function TCrequests($domElement)
{
    echo 'tcrequests';
    $a = $domElement->firstChild;  // la balise a est la 
                                  //1re sous le 2e td d'un tr donne
    $href = $a->getAttribute('href'); //aller chercher URL de la page intermédiaire
    $handle = fopen($href, "r"); //ouverture du flux
    
    $output = '';
    while (!feof($handle)) 
    {
        $output .= fread($handle, 8192); //ajouter a la variable html le contenu de la page intermediaire 
    }
    
fclose($handle);  //fermeture du flux fopen
$crawler = new Crawler($output); //creation d'un objet Crawler pour faciliter le parsing de la page intermediaire
dump($crawler);


    }
}
