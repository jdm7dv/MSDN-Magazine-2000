static String http_reverse(String serverAddress, String s) throws Throwable
{
	java.net.URL url = new java.net.URL(serverAddress);
	java.net.HttpURLConnection conn = (java.net.HttpURLConnection)url.openConnection();
	conn.setRequestMethod("POST");
	conn.setRequestProperty("Content-Type", "text/plain");
	conn.setDoOutput(true);	
	conn.connect();
	java.io.OutputStream out = conn.getOutputStream();
	out.write(s.getBytes());
	out.close();
	java.io.InputStream in = conn.getInputStream();
	byte[] rgb = new byte[1024];
	int cb = in.read(rgb);
	in.close();
	return new String(rgb, 0, cb);
}
