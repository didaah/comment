<?php
// $Id$

function comment_admin_page() {
  dd_set_tabs(array(
    l(t('comment', '评论管理'), 'admin/comment'),
    l(t('comment', '评论字段'), 'admin/comment/fields'),
  ));
  
  if (!empty($_GET['op'])) {
    if ($_GET['op'] == 'delete' && $_GET['cid']) {
      if (comment_delete($_GET['cid'])) {
        echo 'tr';
        exit;
      }
    } else if ($_GET['op'] == 'delete_host' && $_GET['host']) {
      if ($fetch = db_query('SELECT cid FROM {comment} WHERE host = ?', array($_GET['host']))) {
        $count = 0;
        foreach ($fetch as $o) {
          if (comment_delete($o->cid)) {
            $count++;
          }
        }
        dd_set_message(t('comment', '已删除 !count 条评论', array('!count' => $count)));
        echo 'reload';
      }
    }
    exit;
  }
  
  $args = array();
  $query = 'SELECT c.title, c.cid, c.host, c.created, c.body, u.name, c.ext_type FROM {comment} c INNER JOIN {users} u ON c.uid = u.uid';
  if (!empty($_GET['keyword'])) {
    $keyword = '%' . urldecode($_GET['keyword']) . '%';
    $args = array($keyword, $keyword, $keyword);
    $query .= ' WHERE c.host LIKE ? OR c.title LIKE ? OR c.name LIKE ?';
  }
  $query .= ' ORDER BY c.cid DESC';

  $output = dd_get_form('form_admin_search');
  if ($fetch = pager_query($query, 20, 0, NULL, $args)) {
    foreach ($fetch as $o) {
      $o->title .= ' ' . mb_substr(strip_tags($o->body), 0, 50) . '……';
      $table[] = array(
        array(
          'data' => l('+' . $o->title, 'comment/goto/' . $o->cid, array(
            'attributes' => array('target' => '_blank'), 
            'fragment' => 'comment_' . $o->ext_type . '_' . $o->cid
            )),
          'width' => '30%',
        ),
        $o->name,
        array(
          'data' => dd_get_ip($o->host, 1) . '<br/>' .  l('删除', 'admin/comment', array('query' => 'op=delete_host&host=' . $o->host, 'attributes' => array('class' => 'confirmajax'))),
          'width' => '20%' 
        ),
        format_date($o->created),
        l('删除', 'admin/comment', array('query' => 'op=delete&cid=' . $o->cid, 'attributes' => array('class' => 'confirmajax'))),
      );
    }
    
    $output .= theme('table', array('主题', '发布人', '发布者 IP', '发布时间', '操作'), $table, array('class' => 'center_table'));
    $output .= pager_view();
  }
  
  return $output;
}

// public comment_admin_fields() {{{ 
/**
 * comment_admin_fields
 * 评论字段管理
 * 
 * @access public
 * @return string
 */
function comment_admin_fields() {
  $tabs = array(
    l(t('comment', '评论管理'), 'admin/comment'),
    l(t('comment', '评论字段'), 'admin/comment/fields'),
  );
  
  $args = arg();
  
  switch ($args[3]) {
    case 'view':
      $field = new stdClass;
      if (!empty($args[4])) {
        foreach (comment_get_comment_info() as $key => $info) {
          if (('cm_' . $key) == $args[4]) {
            $field->type = 'cm_' . $key;
            break;
          }
        }
      }
       
      if (empty($field->type)) {
        dd_set_message(t('comment', '错误的请求'));
        dd_goto('admin/comment/fields');
      }

      $tabs = array();
      $tabs[] = l(t('comment', '!name属性管理', array('!name' => $info['name'])), 'admin/comment/fields/view/' . $field->type);
      $tabs[] = l(t('comment', '!name属性添加', array('!name' => $info['name'])), 'admin/comment/fields/view/' . $field->type . '/add');
      $tabs[] = l(t('comment', '!name属性导出', array('!name' => $info['name'])), 'admin/comment/fields/view/' . $field->type . '/export');
      $tabs[] = l(t('comment', '!name属性分组', array('!name' => $info['name'])), 'admin/comment/fields/view/' . $field->type . '/groups');
      $tabs[] = l(t('comment', '返回'), 'admin/comment/fields');
      
      switch ($args[5]) {
        case 'add':
          $field->module = 'comment';
          $field->redirect = url('admin/comment/fields/view/' . $field->type);
          $output = dd_get_form('field_form', $field);
        break;
        
        case 'export':
          $output = field_export(0, 'comment', $field->type);
        break;
        
        case 'groups':
          $output = dd_get_form('field_groups', 'comment', $field->type);
        break;

        default:
          $output = field_lists('comment', $field->type);
      }
    break;
   
    default:
      if ($datas = comment_get_comment_info()) {
        $table = array();
        foreach ($datas as $key => $info) {
          $table[] = array(
            $info['name'],
            l('属性管理', 'admin/comment/fields/view/cm_' . $key)
          );
        }
    
        $header = array(
          t('content', '评论类型'),
          t('content', '操作'),
        );

        $output = theme('table', $header, $table, array('class' => 'center_table'));
        $output .= pager_view();
      } else {
        $output = system_no_content();
      }
  }
  
  dd_set_tabs($tabs);
  return $output;
}
// }}}


