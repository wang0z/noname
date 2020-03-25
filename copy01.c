ecd_t tck_allocate_ctx(tck_t *ret)
{
	tck_t	ctx;
	ecd_t	retval;
	char		*time_env;

	retval = xts_get_mem(sizeof(struct tck_struct), &ctx);
	if (retval)
		return retval;

	memset(ctx, 0, sizeof(struct tck_struct));

	ctx->process_inode_size = 256;
	ctx->ext_attr_ver = 2;
	ctx->blocks_per_page = 1;
	ctx->htree_slack_percentage = 255;

	time_env = getenv("TCK_TIME");
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
