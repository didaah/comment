<?php
// $Id$

/**
 * @template 评论默认模板
 * 可根据评论的不同扩展类型，创建不同模板文件。
 * 如：ext_type 为 forum，则可使用 comment_forum.tpl.php
 */

?>

<div id="comment_<?php echo $comment->ext_type?>_<?php echo $comment->cid?>" 
class="comment_view comment_view_<?php echo $zebra; ?> comment_view_<?php echo $comment->ext_type?>">

  <p class="comment_header">
    <strong><?php echo $comment->count;?>.</strong>
    <span class="comment_name">
      <?php if ($comment->site) { ?>
        <a rel="external" target="_blank" href="<?php echo $comment->site; ?>">
          <?php echo $comment->name; ?>
        </a>
        <?php if (!$comment->uid) : ?> (未登录) <?php endif;?>
      <?php } else { ?>
        <?php echo theme('username', $comment); ?>
      <?php } ?>
    </span>
    - <?php echo format_date($comment->created); ?>
    <?php if($comment->title) : ?>
    - <?php echo $comment->title; ?>
    <?php endif?>
    <?php if ($comment->is_create) :?>
      <?php if ($comment->comment_quote) : ?>
      - <a href="#comment_form" rel="nofollow" class="comment_quote" alt="<?php echo $comment->cid; ?>">#引用</a>
      <?php endif ?>
      <?php if ($comment->comment_reply) : ?>
         | <a href="#comment_form" class="comment_reply" alt="<?php echo $comment->cid; ?>" rel="nofollow">#回复</a>
        <?php endif ;?>
    <?php endif ?>
    <?php if ($comment->filter_comment) { ?>
    | <a title="只看<?php echo $comment->name; ?>的评论" href="<?php echo $comment->filter_comment; ?>#comment_view_wrapper" rel="nofollow">#只看<?php echo $comment->name; ?></a>
    <?php } else if ($comment->filter_comment_all) {?>
    | <a title="返回全部评论" href="<?php echo $comment->filter_comment_all; ?>#comment_view_wrapper" rel="nofollow">#返回全部评论</a>
    <?php }?>
  </p>
  <div class="comment_body"><?php echo $comment->body; ?></div>
  
  <?php if($comment->links) : ?>
  <div class="comment_links"><?php echo $comment->links; ?></div>
  <?php endif?>
  
</div>
