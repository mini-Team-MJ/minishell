/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:39:22 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/06/04 23:39:56 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
 * env 배열 안에서 "KEY="로 시작하는 항목의 인덱스를 반환합니다.
 * 없으면 -1을 리턴합니다.
 */
static int	env_index(char **env, const char *key)
{
	int		i;
	size_t	keylen;

	keylen = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		/* env[i]가 "KEY=value" 형태인지 확인 */
		if (ft_strncmp(env[i], key, keylen) == 0 && env[i][keylen] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/*
 * "KEY=value" 형태의 문자열을 만들어 반환합니다.
 * 실패 시 NULL 반환.
 */
static char	*make_var_str(const char *key, const char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

/*
 * envp 안에서 KEY를 찾아서 값을 교체하거나(이미 있으면 free 후 교체),
 * 없으면 배열 크기를 확장해 새로 추가합니다.
 *
 * - envp:      pointer-to-array-of-char*-pointers
 * - key:       예) "PWD", "OLDPWD"
 * - value:     예) "/home/ljh3900/projects"
 *
 * 주의: 'envp' 자체는 malloc으로 할당된 배열이어야 합니다.
 * 그렇지 않으면 realloc()에서 에러가 납니다.
 */
static void	update_env_var(char ***envp, const char *key, const char *value)
{
	int		idx;
	char	*var_str;
	char	**orig;
	char	**resized;
	int		count;

	orig = *envp;
	var_str = make_var_str(key, value);
	if (!var_str)
		return ;
	idx = env_index(orig, key);
	if (idx >= 0)
	{
		/* 이미 존재하면, 기존 문자열을 free하고 새 문자열로 교체 */
		free(orig[idx]);
		orig[idx] = var_str;
	}
	else
	{
		/* 새 변수 추가: 배열 끝까지 개수를 세고 realloc */
		count = 0;
		while (orig[count])
			count++;
		/* count개의 요소 + 새 값 1개 + NULL 종료자 1개 */
		resized = realloc(orig, sizeof(char *) * (count + 2));
		if (!resized)
		{
			free(var_str);
			return ;
		}
		resized[count] = var_str;
		resized[count + 1] = NULL;
		*envp = resized;
	}
}

/*
 * env 배열에서 KEY를 찾아 "value" 부분만 반환합니다.
 * 없으면 errmsg를 stderr로 write하고 NULL 반환.
 * 예: env가 ["HOME=/home/foo", ..., NULL],
 *     ft_getenv_or_err(env, "HOME", "...") → "/home/foo"
 */
static char	*ft_getenv_or_err(char **env, const char *key, const char *errmsg)
{
	int		idx;
	char	*pair;

	idx = env_index(env, key);
	if (idx < 0)
	{
		write(2, errmsg, ft_strlen(errmsg));
		return (NULL);
	}
	pair = env[idx];
	return (ft_strchr(pair, '=') + 1);
}

/*
 * arg을 해석하여 실제 chdir()에 넘길 절대/상대 경로를 반환합니다.
 * alloc_flag가 1로 설정된 경우에는 반환값(path)이 malloc으로 할당된
 * 문자열이므로, 호출부가 사용 후 반드시 free해야 합니다.
 *
 * 동작:
 *   - arg == NULL   or arg == "~"       → HOME 값 반환
 *   - arg인자 배열에 "~/..."로 넘어오면: HOME + (arg + 1) 반환, alloc_flag = 1
 *   - arg == "-"                         → OLDPWD 출력 후 반환
 *   - 그 외                               → arg 그대로 반환
 */
static char	*resolve_path(char *arg, char **env, int *alloc_flag)
{
	char	*home;
	char	*joined;

	*alloc_flag = 0;
	if (!arg || (ft_strncmp(arg, "~", 2) == 0 && ft_strlen(arg) == 1))
	{
		home = ft_getenv_or_err(env, "HOME", "cd: HOME not set\n");
		if (!home)
			return (NULL);
		return (home);
	}
	if (ft_strncmp(arg, "~/", 2) == 0)
	{
		home = ft_getenv_or_err(env, "HOME", "cd: HOME not set\n");
		if (!home)
			return (NULL);
		/* "~/something" 에서 "~" 떼고 "/something" 붙이기 */
		joined = ft_strjoin(home, arg + 1);
		if (!joined)
			write(2, "cd: malloc error\n", 17);
		else
			*alloc_flag = 1;
		return (joined);
	}
	if (ft_strncmp(arg, "-", 2) == 0 && ft_strlen(arg) == 1)
	{
		home = ft_getenv_or_err(env, "OLDPWD", "cd: OLDPWD not set\n");
		if (!home)
			return (NULL);
		/* '-'일 땐 이동 전 값을 출력 */
		write(1, home, ft_strlen(home));
		write(1, "\n", 1);
		return (home);
	}
	return (arg);
}

/*
 * builtin cd
 * - argv: 명령어 토큰 배열. argv[0] == "cd", argv[1]은 이동할 경로(옵션 없음).
 * - envp_ptr: "*"가 가리키는 곳이 malloc으로 만든 char** env 배열이어야 함.
 *
 * 1) 인자 개수 체크: argv[1]과 argv[2]가 모두 있으면 에러 리턴
 * 2) resolve_path로 실제 path(절대/상대/틸드/대시) 구함
 * 3) getcwd(NULL,0)으로 oldpwd 얻어둠(절대 경로)
 * 4) chdir(path) 시도; 실패 시 오류 메시지 출력 후 정리
 * 5) chdir 성공 시 getcwd(NULL,0)으로 newpwd 얻고
 *    update_env_var를 통해 envp에 OLDPWD=oldpwd, PWD=newpwd 갱신
 */
int	ft_cd(char **argv, char ***envp_ptr)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;
	int		alloc_flag;
	char	**env;

	env = *envp_ptr;
	/* 1) 인자 개수 체크 */
	if (argv[1] && argv[2])
		return (write(2, "cd: too many arguments\n", 23), 1);
	/* 2) path 해석 */
	path = resolve_path(argv[1], env, &alloc_flag);
	if (!path)
		return (1);
	/* 3) 이동 전 현재 절대 경로 저장 */
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		if (alloc_flag)
			free(path);
		return (1);
	}
	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		free(oldpwd);
		if (alloc_flag)
			free(path);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_env_var(envp_ptr, "OLDPWD", oldpwd);
	update_env_var(envp_ptr, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	if (alloc_flag)
		free(path);
	return (0);
}
