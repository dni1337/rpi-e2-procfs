/*
 * e2_procfs_frontend.c
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

int e2procfs_frontend_mode_show(struct seq_file *m, void* data)
{
	struct ProcWriteInfo *proc_info = m->private;
	int len = 0;

        if (proc_info->count > 0)
        {
                len = seq_printf(m, "%s\n", proc_info->bpage);
        }
        else
        {
                len = seq_printf(m, "0\n");
        }

        return len;

}

int e2procfs_frontend_mode_write(struct ProcWriteInfo *proc_info, char *kbuf)
{
	int len = 0;

	proc_info->bpage = kbuf;

	return len;
}
