<?php

/* 
 * For more info on msg parts, see https://www.ietf.org/rfc/rfc1730.txt, page 29
 * MIME types are:
 *      0	text
 *      1	multipart
*       2	message
*       3	application
*       4	audio
*       5	image
*       6	video
*       7	other
 */

require_once './../../vendor/autoload.php';


function my_autoload1($class_name){   
    include 'class.' . $class_name . '.inc';
}

spl_autoload_register('my_autoload1');


$inbox = Connect2Gmail::inbox();


//obtenir la date d'aujourd'hui
$today = date("j-M-Y");
//obtenir la source 
$froms = array('FROM "travailleraucanada"','FROM "indeed"','FROM "jobillico"','FROM "ameqenligne"','FROM "alertesemploi-careeralerts@njoyn.com"','FROM "carrieres@workopolis.com"','FROM "diffusion@jobboom.com"');
$emails_from_source = array(array());

// loop through the different from email addresses to create all search strings
for ($i=0;$i<7;$i++) {
    $search_string = $froms[$i] . " SINCE " . $today;
    $emails_from_source[$i] = Message::getEmails($inbox, $search_string);
    
    /* loop through emails from given source if $messages contains emails*/
    if (is_array($emails_from_source[$i]))
    {
        foreach ($emails_from_source[$i] as $msg_number) 
        {
            $current_email = new Message($inbox,$msg_number);
            $structure = imap_fetchstructure($inbox,$msg_number);

            if (!isset($structure->parts)){  // simple msg has no parts
                $current_email->getPart($inbox,$msg_number,$structure,0);  // pass 0 as part-number to getPart

            }
            else {  // multipart msg: cycle through each part
                foreach ($structure->parts as $partno0=>$p){
                    $current_email->getPart($inbox,$msg_number,$p,$partno0+1);
                }
            }
        
        
    switch ($i) 
        {
        case 0:  //travailleraucanada
            echo 'tc';
            Html::TravailCanada($current_email->getHtml());
            break;
        case 1:  //indeed
            Html::Indeed($current_email->getHtml());
            break;
        case 2:  //jobillico
            Html::Jobillico($current_email->getHtml());
            break;  
        case 3:  //ameqenligne
            Html::AmeqEnLigne($current_email->getHtml());
            break;
        case 4:  //groupe perspective
            Html::GroupePerspective($current_email->getHtml());
            break;
        case 5:  //carrieres@workopolis
            Html::Workopolis($current_email->getHtml());
            break;
        case 6:  //diffusion@jobboom
            Html::Jobboom($current_email->getHtml());
            break;
        }
    }
    }
}




		
   


