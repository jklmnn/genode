
with Cai.Log;
with Cai.Log.Client;

procedure Component
is
   I : constant Integer := 42;
   L : constant Long_Integer := 4398046511104;
   NI : constant Integer := -42;
   NL : constant Long_Integer := -4398046511104;
   U : constant Cai.Log.Unsigned := 16#deadbeef#;
begin
   Cai.Log.Client.Info ("Info message");
   Cai.Log.CLient.Warning ("Warning message");
   Cai.Log.Client.Error ("Error message");
   Cai.Log.Client.Info ("Integer: " & Cai.Log.Image (I));
   Cai.Log.Client.Info ("Negative Integer: " & Cai.Log.Image (NI));
   Cai.Log.Client.Info ("Long_Integer: " & Cai.Log.Image (L));
   Cai.Log.Client.Info ("Negative Long_Integer: " & Cai.Log.Image (NL));
   Cai.Log.Client.Info ("Smallest Integer: " & Cai.Log.Image (Integer'First));
   Cai.Log.Client.Info ("Smallest Long_Integer: " & Cai.Log.Image (Long_Integer'First));
   Cai.Log.Client.Info ("Largest Integer: " & Cai.Log.Image (Integer'Last));
   Cai.Log.Client.Info ("Largest Long_Integer: " & Cai.Log.Image (Long_Integer'Last));
   Cai.Log.Client.Info ("True: " & Cai.Log.Image (True));
   Cai.Log.Client.Info ("False: " & Cai.Log.Image (False));
   Cai.Log.Client.Info ("Hex value: " & Cai.Log.Image (U));
   Cai.Log.Client.Info ("Smallest hex value: " & Cai.Log.Image (Cai.Log.Unsigned'First));
   Cai.Log.Client.Info ("Largest hex value: " & Cai.Log.Image (Cai.Log.Unsigned'Last));
end Component;
