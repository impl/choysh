<!--
SPDX-FileCopyrightText: 2022 Noah Fontes

SPDX-License-Identifier: Apache-2.0
-->

# 🥬🥬🥬🥬🥬 Choysh 🥬🥬🥬🥬🥬

> "I don't think this is really a shell, and it certainly isn't in the spirit of Unix." &mdash;Ken Thompson

> "Ken loved bok choy when he was a kid!" &mdash;Ken Thompson's mother

> "The author doesn't even seem to understand how getty works. Now we let this kind of person write shells?" &mdash;impl

Choysh (pronounced "choice") is a shell that lets your users pick what shell they really want. That shell doesn't even have to be in /etc/shells because it's 2022 and if some lonely fool wants to get locked out of your generously provided multi-user Unix system by choosing /bin/false as their shell, they deserve it. Of course they'll come to you to fix their mess, and it's not my fault you're such a personable sysadmin.

To force your poor peons to adopt Choysh, set it as their shell in /etc/passwd (using chsh or whatever). Then they have to symlink ~/.choysh to the shell they want. Otherwise they get /bin/sh. Or, if you're extra nice, you can symlink /etc/choysh to a better default. If you've got some particular ambition you want to crush, ~/.choysh doesn't even have to be a symlink (just executable), so users could write _their own shell_ and install it there. How cool would that be? I bet you'd be so proud. 🥲
