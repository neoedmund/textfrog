package neoe.notifier;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class TheWindow {

	public static void main(String[] args) throws Exception {
		TheWindow w = new TheWindow();
		w.setTimeout(1000);
		w.update("hello");
		Thread.sleep(800);
		w.update("world");
		w.close();
	}

	JFrame f;
	JLabel label;
	private int to=1000;
	private long hideTs;

	public TheWindow() {
		f = new JFrame();
		f.setUndecorated(true);
		f.setAlwaysOnTop(true);
		f.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		f.add(label = new JLabel());
	}

	public void setTimeout(int i) {
		to = i;
	}

	public void update(String s) {
		label.setText(s);
		f.pack();
		f.setLocationRelativeTo(null);
		f.setVisible(true);
		long ts = System.currentTimeMillis() + to;
		if (ts - hideTs > 100) {// not too freq
			hideTs = ts;
			new Thread(() -> {
				try {
					Thread.sleep(to);
					checkHide();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

			}).start();
		}
	}

	private void checkHide() throws InterruptedException {
		while (System.currentTimeMillis() < hideTs) {
			Thread.sleep(10);
		}
		if (f != null)
			f.setVisible(false);
	}

	public void close() {
		f.dispose();
		f = null;
	}

}
