cd `dirname $0`
# See https://docs.gitlab.com/ee/gitlab-basics/create-project.html#push-to-create-a-new-project
# and place all repositories under the cu-ecen-aesd-student-assignments group on gitlab
# Specify the directory above this one as the base for overlay files
./github-classroom-scripts/prsetup.py --create_local --overlay_files .. --push_alternate git@gitlab.com:cu-ecen-aesd-student-assignments "$@"
