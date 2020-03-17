/*
 * This function allocates an e2fsck ctx
 */
errcode_t e2fsck_allocate_ctx(e2fsck_t *ret)
{
	e2fsck_t	ctx;
	errcode_t	retval;
	char		*time_env;

	retval = ext2fs_get_mem(sizeof(struct e2fsck_struct), &ctx);
	if (retval)
		return retval;

	memset(ctx, 0, sizeof(struct e2fsck_struct));

	ctx->process_inode_size = 256;
	ctx->ext_attr_ver = 2;
	ctx->blocks_per_page = 1;
	ctx->htree_slack_percentage = 255;

	time_env = getenv("E2FSCK_TIME");
	if (time_env)
		ctx->now = (time_t) strtoull(time_env, NULL, 0);
	else {
		ctx->now = time(0);
		if (ctx->now < 1262322000) /* January 1 2010 */
			ctx->flags |= E2F_FLAG_TIME_INSANE;
	}

	*ret = ctx;
	return 0;
}
