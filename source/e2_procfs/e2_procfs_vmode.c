/*
 * e2_procfs_vmode.c
 *
 * (c) 2015 SIP-Online
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include "e2_procfs.h"
#include "display/osd/osd_hw.h"
#include <linux/amlogic/vout/vinfo.h>
#include <linux/amlogic/vout/vout_notify.h>

int e2procfs_valpha_show(struct seq_file *m, void* data)
{
	struct ProcWriteInfo *proc_info = m->private;
	int len;

	if (proc_info->count > 0)
	{
		len = seq_printf(m, "%s", proc_info->bpage);
	}
	else
	{
		len = seq_printf(m, "\n");
	}

	return len;
}

int e2procfs_valpha_write(struct ProcWriteInfo *proc_info, char *kbuf)
{
	int len = 0;
	u32  gbl_alpha;

	proc_info->bpage = kbuf;

	if (kstrtouint(kbuf, 0, &gbl_alpha))
		return -EINVAL;

	osd_set_gbl_alpha_hw(0, gbl_alpha);

	return len;
}

int e2procfs_vmode_show(struct seq_file *m, void* data)
{
	int len;
	//const vinfo_t *vinfo;
	struct vinfo_s *vinfo;

	vinfo = get_current_vinfo();

	printk("%s(): get current video mode\n", "e2procfs_vmode_show");
	printk("\tname\t\t\t\t\t:%s\n", vinfo->name);
	printk("\tmode\t\t\t\t\t:%d\n", vinfo->mode);
	printk("\twidth\t\t\t\t\t:%d\n", vinfo->width);
	printk("\theight\t\t\t\t:%d\n", vinfo->height);
	printk("\tfield_height\t\t\t:%d\n", vinfo->field_height);
	printk("\taspect_ratio_num\t\t:%d\n", vinfo->aspect_ratio_num);
	printk("\taspect_ratio_den\t\t:%d\n", vinfo->aspect_ratio_den);
	printk("\tsync_duration_num\t\t:%d\n", vinfo->sync_duration_num);
	printk("\tsync_duration_den\t\t:%d\n", vinfo->sync_duration_den);
	printk("\tscreen_real_width\t\t:%d\n", vinfo->screen_real_width);
	printk("\tscreen_real_height\t:%d\n", vinfo->screen_real_height);
	printk("\tvideo_clk\t\t\t\t:%d\n", vinfo->video_clk);

	len = seq_printf(m, "%s\n", vinfo->name);

	return len;
}

int e2procfs_vmode_write(struct ProcWriteInfo *proc_info, char *kbuf)
{
	int len = 0, ret;
	//vmode_t mode;
	enum vmode_e mode;

	proc_info->bpage = kbuf;

	ret = strlen(kbuf);
    if (ret > 5)
    {
	//	*(_WORD *)(&s + v6) = *(_WORD *)"hz";
	//	*(&s + v6 + 2) = LC0_2[2];
	}

	mode = validate_vmode(kbuf);

	if (mode == VMODE_MAX)
	{
		printk("No valid mode given!\n");
		len = -EFAULT;
	}
	else if (mode != get_current_vmode())
	{
		msleep(500);
		set_current_vmode(mode);
		printk(kbuf);
	}

	return len;
}

int e2procfs_vchoices50_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "720p50 720p 1080i 1080i50 1080p 1080p50\n");

	return len;
}

int e2procfs_vchoices60_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "720p60 720p 1080i 1080i60 1080p 1080p60\n");

	return len;
}

int e2procfs_vmode50_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "1080p50 1080i50 720p50\n");

	return len;
}

int e2procfs_vmode60_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "1080p60 1080i60 720p60\n");

	return len;
}

int e2procfs_vpchoices_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "bestfit letterbox panscan nonlinear\n");

	return len;
}

int e2procfs_vpolicy_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "panscan\n");

	return len;
}

int e2procfs_vachoices_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "any 4:3 16:9 16:10\n");

	return len;
}

int e2procfs_vaspect_show(struct seq_file *m, void* data)
{
	int len;
	const struct vinfo_s *vinfo;

	vinfo = get_current_vinfo();

	len = seq_printf(
		m,
		"%d:%d\n",
		vinfo->aspect_ratio_num,
		vinfo->aspect_ratio_den
	);

	return len;
}

int e2procfs_vpreferred_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "720p 1080i 1080p 720p50 1080i50 1080p50\n");

	return len;
}

int e2procfs_vchoices_show(struct seq_file *m, void* data)
{
	int len = seq_printf(m, "720p 1080i 1080p 720p50 1080i50 1080p50\n");

	return len;
}
