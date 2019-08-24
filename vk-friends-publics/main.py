from collections import defaultdict
from time import sleep
import vk

# If you don't have an access token,
# it can be obtained as vk.AuthSession(app_id='appid', user_login='jake@gmail.com', user_password='Finn').access_token
my_access_token = 'xxxxxx'
GROUP_PREFIX='https://vk.com/public'

def print_top_groups(popular_groups):
    top10 = sorted(popular_groups, key = lambda id: popular_groups[id], reverse=True)[:10]
    for g in top10:
        print(GROUP_PREFIX + str(g))


if __name__ == "__main__":
    session = vk.Session(access_token=my_access_token)
    api = vk.API(session, v='5.101')

    popular_groups = defaultdict(int)

    friend_ids = api.friends.get()['items']
    sleep(0.4)

    my_groups = api.groups.get()['items']


    # print(friend_ids)
    for friend_id in friend_ids:
        print(friend_id)
        sleep(0.4)
        try:
            groups = api.groups.get(user_id=friend_id)['items']
            for group in groups:
                if group not in my_groups:
                    popular_groups[group] += 1
        except:
            pass

    top = sorted(popular_groups, key = lambda id: popular_groups[id], reverse=True)
    print(top)

    with open("result.html", 'w') as result:
        for g in top:
            result.write('<a href="https://vk.com/public' + str(g) + '">' + str(g) + "/><br>")

