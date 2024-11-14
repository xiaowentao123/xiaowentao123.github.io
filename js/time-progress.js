// 获取当前时间信息
function updateProgress() {
    const today = new Date();
    
    // 本年已经过去了多少月
    const startOfYear = new Date(today.getFullYear(), 0, 1);
    const monthsPassed = today.getMonth();
    const monthsInYear = 12;
    const monthProgress = (monthsPassed + today.getDate() / 30) / monthsInYear;

    // 本月已经过去了多少天
    const startOfMonth = new Date(today.getFullYear(), today.getMonth(), 1);
    const daysInMonth = new Date(today.getFullYear(), today.getMonth() + 1, 0).getDate();
    const daysPassed = today.getDate();
    const dayProgress = daysPassed / daysInMonth;

    // 今天已经过去了多少小时
    const hoursInDay = 24;
    const hoursPassed = today.getHours() + today.getMinutes() / 60;
    const dayProgressInHours = hoursPassed / hoursInDay;

    // 更新进度条和显示文本
    document.getElementById('year-progress').textContent = `今年已过：${Math.floor(monthsPassed + today.getDate() / 30)}个月`;
    document.getElementById('year-progress-bar').style.width = `${monthProgress * 100}%`;

    document.getElementById('month-progress').textContent = `本月已过：${daysPassed}天`;
    document.getElementById('month-progress-bar').style.width = `${dayProgress * 100}%`;

    document.getElementById('day-progress').textContent = `今天已过：${Math.floor(hoursPassed)}小时`;
    document.getElementById('day-progress-bar').style.width = `${dayProgressInHours * 100}%`;
}

// 每秒更新一次
setInterval(updateProgress, 1000);

// 页面加载时立即执行一次
updateProgress();
