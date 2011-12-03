<?php
// $Id$

function comment_admin_page() {
  
  if (!empty($_GET['op']) && $_GET['op'] == 'delete' && $_GET['cid']) {
    if (comment_delete($_GET['cid'])) {
      echo 'tr';
    }
    exit;
  }
  
  if ($fetch = pager_query('SELECT c.title, c.cid, c.host, c.created, u.name FROM {comment} c INNER JOIN {users} u 
  ON c.uid = u.uid ORDER BY cid DESC', 20)) {
    
    foreach ($fetch as $o) {
      $table[] = array(
        l($o->title, 'comment/goto/' . $o->cid, array('attributes' => array('target' => '_blank'))),
        $o->name, $o->host, format_date($o->created),
        l('删除', 'admin/comment', array('query' => 'op=delete&cid=' . $o->cid, 'attributes' => array('class' => 'confirmajax')))
      );
    }
    
    $output = theme('table', array('主题', '发布人', '发布者 IP', '发布时间', '操作'), $table, array('class' => 'center_table'));
    $output .= pager_view();
  }
  
  return $output;
}