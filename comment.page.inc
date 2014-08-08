<?php
// $Id$

/**
 * 删除评论
 * @param (object) $comment
 *  评论对象
 */
function comment_page_delete($comment) {
  if (comment_delete($comment)) {
    if (!empty($_GET['ajax'])) {
      echo 'ok';
      exit;
    }
    dd_set_message(t('comment', '删除成功'));
  } else if (!empty($_GET['ajax'])) {
    echo 'error';
    exit;
  } else {
    dd_set_message(t('comment', '删除失败'), 'error');
  }
  
  if (!empty($_GET['redirect'])) {
    $url = $_GET['redirect'];
  } else if (!empty($comment->redirect)) {
    $url = $comment->redirect;
  } else {
    $url = NULL;
  }

  dd_goto($url);
}

/**
 * 编辑评论
 * @param (object) $comment
 *  评论对象
 */
function comment_page_edit($comment) {
  $info = comment_get_comment_info($comment->ext_type);
  dd_set_title(array(t('comment', '编辑!name', array('!name' => $info['name']))));
  
  return dd_get_form('comment_form', $comment);
}

/**
 * 屏蔽评论
 * @param (object) $comment
 *  评论对象
 */
function comment_page_hide($comment) {
  if (db_exec('UPDATE {comment} SET status = 2 WHERE cid = ?', array($comment->cid))) {
    dd_set_message(t('comment', '屏蔽成功'));
  } else {
    dd_set_message(t('comment', '屏蔽失败'), 'error');
  }
  
  if (!empty($_GET['redirect'])) {
    $url = $_GET['redirect'];
  } else if (!empty($comment->redirect)) {
    $url = $comment->redirect;
  } else {
    comment_page_goto($comment);
  }

  dd_goto($url);
}

/**
 * 根据评论 id 跳转到所属节点
 * @param (object) $comment
 *  评论对象
 */
function comment_page_goto($comment) {
  if ($urls = module_invoke_all('comment_goto', $comment)) {
    dd_goto(is_array($urls) ? $urls[0] : $urls);
  } else {
    dd_goto(NULL);
  }
}

// public comment_page_type($type) {{{ 
/**
 * comment_page_type
 * 按类型浏览所有评论
 * 
 * @param array $type 
 * @access public
 * @return string
 */
function comment_page_type($type) {
  $type = (object) $type;
  $type->ext_type = $type->key;
  // $type->content
  module_invoke_all('comment_type', $type);

  dd_add_css(dd_get_path('module', 'comment').'/comment.css');

  if (empty($type->content)) {
    dd_set_title(array($type->name));
    if ($fetch = pager_query('SELECT * FROM {comment} WHERE ext_type = ? AND status > 0 ORDER BY created DESC',
    20, 0, NULL, array($type->key))) {
      $item = array();
      foreach ($fetch as $o) {
        $o->url = 'comment/goto/' . $o->cid;
        module_invoke_all('comment_fields', $o);
        $text = '<div>' . $o->body . '</div>';
        $text .= '<div class="links">' . theme('username', $o);
        $text .= t('comment', '评论于');
        $text .= l(format_date($o->created), $o->url, array('fragment' => 'comment_' . $o->ext_type . '_' . $o->cid));
        $text .= '</div>';
        $item[] = $text;
      }
      $type->content = theme('item_list', $item, $type->name, 'ul', array('id' => 'comment_type_list'));
      $type->content .= pager_view();
    }
  }

  return theme('comment_type', $type);
}
// }}}
