<?php

/*
 +-----------------------------------------------------------------------+
 | program/steps/mail/copy.inc                                           |
 |                                                                       |
 | This file is part of the Roundcube Webmail client                     |
 | Copyright (C) 2005-2010, Roundcube Dev. - Switzerland                 |
 | Licensed under the GNU GPL                                            |
 |                                                                       |
 | PURPOSE:                                                              |
 |   Copy the submitted messages to a specific mailbox                   |
 |                                                                       |
 +-----------------------------------------------------------------------+
 | Author: Aleksander Machniak <alec@alec.pl>                            |
 +-----------------------------------------------------------------------+

 $Id: copy.inc 4321 2010-12-08 12:52:04Z alec $

*/

// only process ajax requests
if (!$OUTPUT->ajax_call)
  return;

// move messages
if (!empty($_POST['_uid']) && !empty($_POST['_target_mbox'])) {
    $uids = get_input_value('_uid', RCUBE_INPUT_POST);
    $target = get_input_value('_target_mbox', RCUBE_INPUT_POST, true);
    $mbox = get_input_value('_mbox', RCUBE_INPUT_POST, true);

    $copied = $IMAP->copy_message($uids, $target, $mbox);

    if (!$copied) {
        // send error message
        rcmail_display_server_error('errorcopying');
        $OUTPUT->send();
        exit;
    }
    else {
        $OUTPUT->show_message('messagecopied', 'confirmation');
    }

    rcmail_send_unread_count($target, true);

    $OUTPUT->command('set_quota', rcmail_quota_content());
}
// unknown action or missing query param
else {
    exit;
}

// send response
$OUTPUT->send();
