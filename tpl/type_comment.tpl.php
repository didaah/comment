<?php
// $Id$

/**
 * @template 评论类型列表页
 * 可根据评论的不同扩展类型，创建不同模板文件。
 * 如：ext_type 为 forum，则可使用 type_comment_forum.tpl.php
 * @param object $type
 */
?>

<div id="type_comment_<?php echo $type->ext_type?>" class="type_comment_view type_comment_view_<?php echo $type->ext_type?>">
  <?php echo $type->content; ?>
</div>



