public class ReverseServlet extends javax.servlet.http.HttpServlet
{
    public void doPost(javax.servlet.http.HttpServletRequest request, 
                       javax.servlet.http.HttpServletResponse response) 
                 throws java.io.IOException
    {
        byte[] rgb = new byte[request.getContentLength()];
        int cb = request.getInputStream().read(rgb);
        StringBuffer sb = new StringBuffer(new String(rgb, 0, cb));
        response.getWriter().print(sb.reverse());		
    }
}
