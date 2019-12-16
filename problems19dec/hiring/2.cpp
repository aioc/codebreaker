#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum EventType {
    GREATER_SKILL = 1,
    MONK = 2,
    LESS_SKILL = 3,
};

struct event {
    EventType type;
    int skill;
    event(EventType t, int s) : type{t}, skill{s} {}

    bool operator<(const event& oth) const {
        // Sort by ascending skill first,
        // then tie break by ascending type (i.e. master jobs first,
        // then monks, then student jobs).
        return make_pair(skill, type) < make_pair(oth.skill, oth.type);
    }
};

vector<event> e;

int main() {
    for(auto eventType: {MONK, LESS_SKILL, GREATER_SKILL}) {
        int N;
        cin >> N;
        for(int i = 0; i < N; i++) {
            int x;
            cin >> x;
            e.emplace_back(eventType, x);
        }
    }
    
    // Sort according to the event struct's custom comparator.
    sort(e.begin(), e.end());

    int ans = 0;
    int monks = 0;
    int jobs = 0;
    for(auto x: e) {
        if(x.type == MONK) {
            if(jobs) {
                // If a job exists from past events, take it.
                jobs--;
                ans++;
            } else {
                // Otherwise, they can take a future event.
                monks++;
            }
        } else if(x.type == GREATER_SKILL) {
            // Any monk from this point onwards
            // can take this job
            jobs++;
        } else if(x.type == LESS_SKILL) {
            if(monks) {
                // If a monk exists from past events, take it.
                monks--;
                ans++;
            }
            // } else {
            //      There are no monks available to take this job
            //      and all future monks will have a skill level
            //      that is too high.
            //
            //      Therefore, discard this job.
            // }
        }
    }
    cout << ans << "\n";
}
