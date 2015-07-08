<?php

/* 
 * Email parsing functions
 */


class Message  {
  
    private $msgid;
    private $htmlmsg;

    
/* function to extract body part data from a message
 * @param $inbox = imap stream
 * @param $msgid = message id
 * then calls getPart once (for simple msg) or recursively (for each part
 * of a multipart msg. 
 * 

 */
    
function __construct ($inbox,$msgid) {
       
    $this->htmlmsg = "";
    $this->msgid = $msgid;
    }


//getEmails returns $messages = array of emails
public static function getEmails($inbox, $search_string)
{
    $messages = imap_search($inbox,$search_string);  
    return $messages; 
}    
  

function getPart($inbox,$msgid,$p,$partno) {
    
    // DECODE DATA
    $data = ($partno)?
        imap_fetchbody($inbox,$msgid,$partno):  // multipart    
        imap_body($inbox,$msgid);  // simple
        
        
    // Any part may be encoded, even plain text messages, so check everything.
    if ($p->encoding==4){
        $data = quoted_printable_decode($data);
    }
    elseif ($p->encoding==3){
        $data = base64_decode($data);
    }
    
    
    // ADD TEXT to htmlmsg string
    if ($p->type==0 && $data) {
        // Messages may be split in different parts because of inline attachments,
        // so append parts together with blank row.
        if (strtolower($p->subtype)=='html')
        {
            $this->htmlmsg .= $data ."<br><br>";
        }
    }

    // SUBPART RECURSION
    if (isset($p->parts)) {
        foreach ($p->parts as $partno0=>$p2){
            $this->getPart($inbox,$msgid,$p2,$partno.'.'.($partno0+1));  // 1.2, 1.2.1, etc.
            }
    }
}

public function getHtml(){
    return $this->htmlmsg;
}
}
