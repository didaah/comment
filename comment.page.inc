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
    dd_set_message('删除成功');
  } else if (!empty($_GET['ajax'])) {
    echo 'error';
    exit;
  } else {
    dd_set_message('删除失败', 'error');
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
 * 根据评论 id 跳转到所属节点
 * @param (object) $comment
 *  评论对象
 */
function comment_page_goto($comment) {
  if ($url = module_invoke_first('comment_goto', $comment)) {
    dd_goto($url);
  } else {
    dd_goto(NULL);
  }
}
